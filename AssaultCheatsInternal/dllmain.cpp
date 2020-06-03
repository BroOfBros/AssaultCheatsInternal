// The dll entry point.

#include "stdafx.h"
#include "Game.h"
#include "Hook.h"
#include "Memory.h"

// The game state space
Game* game;

/**
 * The main 'cheat' loop.
 */
BOOL __stdcall hWglSwapBuffers(HDC hDc) {
	// @@@ TODO: actual hacks @@@

	// Enable triggerbot
	if (GetAsyncKeyState(VK_F1) & 1) {
		Triggerbot* trigger = game->getHacks()->trigger;

		if (trigger->isEnabled()) {
			trigger->disable();
			game->printTop("Triggerbot %sdisabled!", red);
		}
		else {
			trigger->enable();
			game->printTop("Triggerbot %senabled!", green);
		}
	}

	// Update game state
	game->update();
	return game->oWglSwapBuffers(hDc);
}

/**
 * Initialize the game state space.
 */
DWORD WINAPI init(HMODULE module) {
	// Create an external console
	AllocConsole();
	FILE* console;
	freopen_s(&console, "CONOUT$", "w", stdout);

	// Init game state space
	game = new Game(
		module, console,
		new Hook(L"opengl32.dll", "wglSwapBuffers", (DWORD)hWglSwapBuffers, 5));

	while (1) {
		// Unhook by pressing the 'END'
		if ((GetAsyncKeyState(VK_END) & 1)) {
			game->printTop("%sUnhooking...", lightRed);
			delete game;
			break;
		}

		// Wait for hook to finish unloading
		Sleep(100);
	}

	return EXIT_SUCCESS;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call,
					  LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)init, hModule,
									 0, NULL));
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}
