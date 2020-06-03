#include "stdafx.h"
#include "Memory.hpp"

MODULEINFO Memory::getModule(const WCHAR* name) {
	HANDLE proc = GetCurrentProcess();
	HMODULE moduleHandle = GetModuleHandleW(name);

	MODULEINFO info;
	GetModuleInformation(proc, moduleHandle, &info, sizeof(MODULEINFO));

	return info;
}

DWORD Memory::resolveAddr(DWORD addr, std::vector<DWORD> offsets) {
	for (DWORD offset : offsets) {
		addr = *(DWORD*)addr;
		addr += offset;
	}

	return addr;
}

void Memory::write(DWORD addr, const BYTE* bytes, SIZE_T n) {
	DWORD old;
	VirtualProtect((LPVOID)addr, n, PAGE_EXECUTE_READWRITE, &old);
	memcpy((void*)addr, bytes, n);
	VirtualProtect((LPVOID)addr, n, old, &old);
}

void Memory::nop(DWORD addr, BYTE* oldBytes, SIZE_T n) {
	if (oldBytes != NULL) {
		memcpy(oldBytes, (void*)addr, n);
	}

	BYTE* arr = new BYTE[n];
	memset(arr, 0x90, n);
	write(addr, arr, n);
	delete[] arr;
}
