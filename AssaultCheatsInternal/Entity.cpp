#include "stdafx.h"
#include "Entity.hpp"

Entity::Entity(DWORD base) {
	this->base = base;

	// TODO: init offsets struct
	offsets = {
		{0x04, 0x08, 0x0C},
		{0xF8}
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