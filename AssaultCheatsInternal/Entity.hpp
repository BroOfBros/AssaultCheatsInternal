// An abstract representation of an ingame entity.
#pragma once
#include "stdafx.h"

typedef struct {
	std::vector<DWORD> headPos;	// 0 -> X, 1 -> Y, 2 -> Z
	std::vector<DWORD> health;
	std::vector<DWORD> armor;
	std::vector<DWORD> attack;
	std::vector<DWORD> scope;
} EntOffsets;

class Entity {
public:
	Entity(DWORD base);

	std::vector<float> getHeadPos();
	int getHealth();

protected:
	DWORD base;
	EntOffsets offsets;
};