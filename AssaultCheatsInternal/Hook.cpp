#include "stdafx.h"
#include "Hook.hpp"

Hook::Hook(DWORD src, DWORD dest, SIZE_T len) {
	this->src = src;
	this->dest = dest;
	this->len = len;
	originalBytes = NULL;
	gateway = 0;
	enabled = FALSE;
}

Hook::Hook(const WCHAR* moduleName, const CHAR* funcName, DWORD dest,
		   SIZE_T len) {
	this->src = (DWORD)GetProcAddress(GetModuleHandle(moduleName), funcName);
	this->dest = dest;
	this->len = len;
	originalBytes = NULL;
	gateway = 0;
	enabled = FALSE;
}

Hook::~Hook() {
	if (isEnabled()) {
		disable();
	}
}

void Hook::detour(DWORD src, DWORD dest, SIZE_T len) {
	if (len < 5) {
		return;
	}

	// Nop the original bytes
	Memory::nop(src, NULL, len);

	// Detour execution from source to destination
	DWORD old;
	VirtualProtect((LPVOID)src, len, PAGE_EXECUTE_READWRITE, &old);

	DWORD destRelAddr = dest - src - 5;

	*(DWORD*)src = 0xE9;
	*(DWORD*)(src + 1) = destRelAddr;

	VirtualProtect((LPVOID)src, len, old, &old);
}

DWORD Hook::trampHook(DWORD src, DWORD dest, SIZE_T len) {
	if (len < 5) {
		return src;
	}

	// Create gateway and write the stolen bytes to it
	DWORD gateway = (DWORD)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE,
										PAGE_EXECUTE_READWRITE);
	memcpy((void*)gateway, (void*)src, len);

	// Jump from the gateway back to the source address (after the stolen bytes)
	DWORD gatewayRelAddr = src - gateway - 5;

	*(DWORD*)(gateway + len) = 0xE9;
	*(DWORD*)(gateway + len + 1) = gatewayRelAddr;

	// Perform detour
	detour(src, dest, len);
	return gateway;
}

DWORD Hook::enable() {
	originalBytes = new BYTE[len];
	memcpy(originalBytes, (const void*)src, len);

	enabled = TRUE;
	gateway = trampHook(src, dest, len);

	return gateway;
}

void Hook::disable() {
	Memory::write(src, originalBytes, len);

	enabled = FALSE;
	delete[] originalBytes;
	VirtualFree((LPVOID)gateway, 0, MEM_RELEASE);
}

BOOL Hook::isEnabled() {
	return enabled;
}