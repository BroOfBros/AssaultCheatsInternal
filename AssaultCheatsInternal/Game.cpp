#include "stdafx.h"
#include "Game.h"

Game::Game(HMODULE module, FILE* console, Hook* hook) {
	// Init state
	this->module = module;
	this->console = console;
	this->hook = hook;
	oWglSwapBuffers = (tWglSwapBuffers)hook->enable();

	// Get offsets
	offsets = new Offsets();
	initOffsets();

	// Init hacks
	hacks = new Hacks();
	hacks->trigger = new Triggerbot(offsets->playersList, offsets->playersCount, offsets->inCross);
}

Game::~Game() {
	if (hook->isEnabled()) {
		hook->disable();
	}

	delete offsets;
	delete hacks;
	fclose(console);
	FreeConsole();

	Sleep(100);
	FreeLibraryAndExitThread(module, 0);
}

void Game::initOffsets() {
	offsets->moduleAddr = (DWORD)Memory::getModule(NULL).lpBaseOfDll;

	offsets->player = offsets->moduleAddr + 0x10F4F4;
	offsets->playersCount = offsets->moduleAddr + 0x10F500;
	offsets->playersList = offsets->moduleAddr + 0x10F4F8;

	offsets->printTop = (tPrintTop)tPrintTopAddr;
	offsets->inCross = (tInCross)tInCrossAddr;

	printTop = offsets->printTop;
}

Hacks* Game::getHacks() {
	return hacks;
}

void Game::update() {
	hacks->trigger->execute();
}