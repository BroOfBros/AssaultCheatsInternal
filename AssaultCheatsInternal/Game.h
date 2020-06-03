// The game state space class.

#pragma once
#include "stdafx.h"
#include "Memory.h"
#include "Hook.h"
#include "SwapBuffers.h"
#include "IngameText.h"
#include "Aim.h"
#include "Triggerbot.h"

struct Offsets {
	DWORD moduleAddr;

	DWORD player;
	DWORD playersList;
	DWORD playersCount;

	/**
	* Print a message ingame at the top right corner.
	*/
	tPrintTop printTop;

	/**
	 * Returns the address of the entity the player is aiming at.
	 */
	tInCross inCross;
};

class Hacks {
public:
	~Hacks() {
		delete trigger;
	}

	Triggerbot* trigger;
};

class Game {
public:
	Game(HMODULE module, FILE* console, Hook* hook);
	~Game();

	void initOffsets();
	Hacks* getHacks();

	/**
	 * Update the current game state.
	 */
	void update();

	/**
	 * A pointer to the gateway function.
	 */
	tWglSwapBuffers oWglSwapBuffers;

	tPrintTop printTop;

private:
	HMODULE module;
	FILE* console;
	Hook* hook;

	Offsets* offsets;
	Hacks* hacks;
};