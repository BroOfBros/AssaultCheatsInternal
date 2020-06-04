#include "stdafx.h"
#include "Game.hpp"

Game::Game(DWORD hWglSwapBuffers) {
	hook = new Hook(L"opengl32.dll", "wglSwapBuffers", (DWORD)hWglSwapBuffers, 5);
	offsets.oWglSwapBuffers = oWglSwapBuffers = (tWglSwapBuffers)hook->enable();

	init();
}

Game::~Game() {
	offsets.printTop("%sUnhooking...", red);

	if (hook->isEnabled()) {
		hook->disable();
	}

	delete hook;

	// Free hacks
	delete hacks.triggerBot;

	// Free other
	delete player;
}

void Game::init() {
	// Offsets
	offsets.printTop = (tPrintTop)0x0046B060;
	offsets.getEntInCross = (tInCross)0x004607C0;

	offsets.mod = (DWORD)Memory::getModule(NULL).lpBaseOfDll;
	offsets.player = offsets.mod + 0x10F4F4;
	offsets.entCount = offsets.mod + 0x10F500;
	offsets.entList = offsets.mod + 0x10F4F8;

	// Hacks
	hacks.triggerBot = new Triggerbot(&offsets);

	// Others
	player = new Entity(offsets.player);
}

void Game::update() {
	if (hacks.triggerBot->isEnabled()) {
		hacks.triggerBot->execute();
	}
}

void Game::toggleTriggerBot() {
	hacks.triggerBot->toggle();

	if (hacks.triggerBot->isEnabled()) {
		offsets.printTop("Triggerbot %senabled!", green);
	}
	else {
		offsets.printTop("Triggerbot %sdisabled!", red);
	}
}
