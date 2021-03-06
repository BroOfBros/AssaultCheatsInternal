#include "stdafx.h"
#include "Game.hpp"

// The game state space
Game* game;

/**
 * The main 'cheat' loop.
 */
BOOL __stdcall hWglSwapBuffers(HDC hDc) {
	// TriggerBot
	if (GetAsyncKeyState(VK_F1) & 1) {
		game->toggleTriggerBot();
	}

	// Update game state
	game->update();
	return game->oWglSwapBuffers(hDc);
}

/**
 * Initialize the game state space.
 */
DWORD WINAPI init(HMODULE hModule) {
	// Create an external console
	AllocConsole();
	FILE* console;
	freopen_s(&console, "CONOUT$", "w", stdout);

	// Init game state space
	game = new Game((DWORD)hWglSwapBuffers);

	while (1) {
		// Unhook by pressing the 'END'
		if ((GetAsyncKeyState(VK_END) & 1)) {
			delete game;
			break;
		}

		// Wait for hook to finish unloading
		Sleep(100);
	}

	fclose(console);
	FreeConsole();

	Sleep(100);
	FreeLibraryAndExitThread(hModule, EXIT_SUCCESS);
	return EXIT_SUCCESS;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)init, hModule, 0, NULL));
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}

	return TRUE;
}
