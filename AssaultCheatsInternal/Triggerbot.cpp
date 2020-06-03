#include "stdafx.h"
#include "Triggerbot.hpp"

Triggerbot::Triggerbot(Offsets* offsets) {
	this->offsets = offsets;
}

void Triggerbot::execute() {
	int n = *(DWORD*)offsets->entCount;
	DWORD entList = offsets->entList;

	for (int i = 0; i < n; i++) {
		DWORD entity = Memory::resolveAddr(entList, { 4UL * i });

		if (*(DWORD*)entity && offsets->getEntInCross() == *(DWORD*)entity) {
			char* name = (char*)(DWORD*)Memory::resolveAddr(entity, { 0x225 });
			printf("0x%.8X : %s\n", entity, name);
		}
	}
}