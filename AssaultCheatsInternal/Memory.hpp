// An internal memory library.
#pragma once

#include "stdafx.h"
#include <TlHelp32.h>
#include <Psapi.h>

namespace Memory {
	/**
	 * Get informations about a given module.
	 */
	MODULEINFO getModule(const WCHAR* name);

	/**
	* Resolve an address based on the given offsets.
	* Returns the resolved address.
	*/
	DWORD resolveAddr(DWORD addr, std::vector<DWORD> offsets);

	/**
	 * Write n bytes at the given address.
	 */
	void write(DWORD addr, const BYTE* bytes, SIZE_T n);

	/**
	 * Nops n bytes from the given address.
	 * Returns the nopped bytes by the second parameter.
	 * If the second argument is NULL, it will be ignored.
	 */
	void nop(DWORD addr, BYTE* oldBytes, SIZE_T n);
}