// The game state space class.
#pragma once
#include "stdafx.h"

// Hooks and offsets
#include "Hook.hpp"
#include "Offsets.h"

// Hacks
#include "Triggerbot.hpp"

// Other
#include "Entity.hpp"

typedef struct {
	Triggerbot* triggerBot;
} Hacks;

class Game {
public:
	Game(DWORD hWglSwapBuffers);
	~Game();

	// We need a reference to it inside dllmain.
	tWglSwapBuffers oWglSwapBuffers;

	void init();
	void update();
	void toggleTriggerBot();

private:
	// Hooks and offsets
	Hook* hook;
	Offsets offsets;

	// Hacks
	Hacks hacks;

	// Other
	Entity* player;
};