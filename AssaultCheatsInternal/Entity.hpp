// An abstract representation of an ingame entity.
#pragma once
#include "stdafx.h"

typedef struct {
	std::vector<DWORD> headPos;	// 0 -> X, 1 -> Y, 2 -> Z
	std::vector<DWORD> scoping;
	std::vector<DWORD> health;
	std::vector<DWORD> armor;
	std::vector<DWORD> attack;
	std::vector<DWORD> name;
	std::vector<DWORD> team;
	std::vector<DWORD> scope;
} EntOffsets;

class Entity {
public:
	Entity(DWORD base);

	std::vector<float> getHeadPos();
	int getHealth();
	char* getName();
	int getTeam();

protected:
	DWORD base;
	EntOffsets offsets;
};