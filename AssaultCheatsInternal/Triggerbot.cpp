#include "stdafx.h"
#include "Triggerbot.h"
#include "Memory.h"

Triggerbot::Triggerbot(DWORD playersList, DWORD playersCount, tInCross inCross) {
	this->playersList = playersList;
	this->playersCount = playersCount;
	this->inCross = inCross;
	enabled = FALSE;
}

Triggerbot::~Triggerbot() {
}

BOOL Triggerbot::isEnabled() {
	return enabled;
}

void Triggerbot::enable() {
	this->enabled = TRUE;
}

void Triggerbot::disable() {
	this->enabled = FALSE;
}

void Triggerbot::execute() {
	if (isEnabled()) {
		int n = *(DWORD*)playersCount;

		for (int i = 0; i < n; i++) {
			DWORD entity = Memory::resolveAddr(playersList, { 4UL * i });

			if (*(DWORD*)entity && inCross() == *(DWORD*)entity) {
				char* name = (char*)(DWORD*)Memory::resolveAddr(entity, { 0x225 });
				printf("0x%.8X : %s\n", entity, name);
			}
		}
	}
}