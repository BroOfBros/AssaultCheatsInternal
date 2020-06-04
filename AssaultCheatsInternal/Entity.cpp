#include "stdafx.h"
#include "Entity.hpp"

Entity::Entity(DWORD base) {
	this->base = base;

	offsets = {
		{0x04, 0x08, 0x0C},
		{0x71},
		{0xF8},
		{0xFC},
		{0x224},
		{0x225},
		{0x32C},
		{ 0x374, 0x28 },
	};
}

std::vector<float> Entity::getHeadPos() {
	std::vector<float> pos = {
		(float)*(DWORD*)Memory::resolveAddr(base, {offsets.headPos[0]}),
		(float)*(DWORD*)Memory::resolveAddr(base, {offsets.headPos[1]}),
		(float)*(DWORD*)Memory::resolveAddr(base, {offsets.headPos[2]})
	};

	return pos;
}

int Entity::getHealth() {
	return (int)*(DWORD*)Memory::resolveAddr(base, offsets.health);
}

char* Entity::getName() {
	return (char*)(DWORD*)Memory::resolveAddr(base, offsets.name);
}

int Entity::getTeam() {
	return (int)*(DWORD*)Memory::resolveAddr(base, offsets.team);
}
