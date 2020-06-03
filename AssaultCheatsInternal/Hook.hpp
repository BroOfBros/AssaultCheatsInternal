// An internal trampoline hook class.
#pragma once
#include "stdafx.h"

class Hook {
public:
	/**
	 * Specify the source address, the destination address and the number of bytes
	 * to steal.
	 */
	Hook(DWORD src, DWORD dest, SIZE_T len);

	/**
	 * Use this when hooking into a library function.
	 * EG: hooking OpenGL functions, DirectX, etc.
	 * Usage: Hook("opengl32.dll", "wglSwapBuffers", 0xDEADBEEF, 5);
	 */
	Hook(const WCHAR* moduleName, const CHAR* funcName, DWORD dest, SIZE_T len);

	~Hook();

	/**
	* Detour execution from the source address to the destination address.
	* The minimum size for the detour to happen is len = 5 bytes.
	* 1 byte is the jmp instruction, and 4 bytes for the destination address.
	* For values of len < 5 the detour will fail.
	*/
	void detour(DWORD src, DWORD dest, SIZE_T len);

	/**
	* Do a trampoline hook from the source address to the destination address.
	*/
	DWORD trampHook(DWORD src, DWORD dest, SIZE_T len);

	/**
	 * Enable hook.
	 * Returns the address of the gateway function.
	 */
	DWORD enable();

	/**
	 * Disable hook.
	 * On disable, the stolen bytes will be returned to their source and virtual
	 * allocated memory will be freed.
	 */
	void disable();

	/**
	 * Returns TRUE if the hook is enabled, else FALSE.
	 */
	BOOL isEnabled();

private:
	DWORD src;
	DWORD dest;
	SIZE_T len;

	BYTE* originalBytes = NULL;
	DWORD gateway = 0;

	BOOL enabled = FALSE;
};

