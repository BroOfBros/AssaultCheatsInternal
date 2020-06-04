#include "stdafx.h"
#include "Triggerbot.hpp"
#include "Entity.hpp"
#include "Player.hpp"

Triggerbot::Triggerbot(Offsets* offsets) {
	this->offsets = offsets;
	enabled = FALSE;
}

void Triggerbot::toggle() {
	enabled = !enabled;
}

BOOL Triggerbot::isEnabled() {
	return enabled;
}

void Triggerbot::execute() {
	Player* player = new Player(offsets->player);
	DWORD targetBase = offsets->getEntInCross();

	if (targetBase) {
		Entity* target = new Entity((DWORD)&targetBase);
		printf("%s: %d\n", target->getName(), target->getHealth());
		player->shoot(target->getTeam() != player->getTeam());

		delete target;
	}
	else {
		player->shoot(FALSE);
	}

	delete player;
}