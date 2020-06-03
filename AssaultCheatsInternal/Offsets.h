// Reversed structures and data from AC.
#pragma once
#include "stdafx.h"

#pragma region Functions

// OpenGL wglSwapBuffers
typedef BOOL(__stdcall* tWglSwapBuffers) (HDC hDc);

#pragma region Ingame

// Print a message at the top right corner
typedef char* (__stdcall* tPrintTop) (char* formatString, ...);

// and some text colors
constexpr auto green = "\x0C\x30";
constexpr auto blue = "\x0C\x31";
constexpr auto yellow = "\x0C\x32";
constexpr auto lightRed = "\x0C\x33";
constexpr auto grey = "\x0C\x34";
constexpr auto white = "\x0C\x35";
constexpr auto darkRed = "\x0C\x36";
constexpr auto red = "\x0C\x37";
constexpr auto purple = "\x0C\x38";
constexpr auto orange = "\x0C\x39";

// Return entity in crosshair
typedef int(__stdcall* tInCross)();

#pragma endregion

#pragma endregion

#pragma region Offsets

typedef struct {
	// Hooks
	tWglSwapBuffers oWglSwapBuffers;
	
	// Ingame functions
	tPrintTop printTop;
	tInCross getEntInCross;

	// Ingame offsets
	DWORD mod;
	DWORD player;
	DWORD entList;
	DWORD entCount;
} Offsets;

#pragma endregion