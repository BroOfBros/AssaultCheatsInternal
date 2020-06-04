// The player class.
#pragma once
#include "Entity.hpp"

class Player : public Entity {
public:
	Player(DWORD base);

	void shoot(BOOL toggle);
};