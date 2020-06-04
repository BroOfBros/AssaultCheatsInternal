#include "stdafx.h"
#include "Player.hpp"

Player::Player(DWORD base) : Entity(base) {
}

void Player::shoot(BOOL toggle) {
	DWORD shooting = Memory::resolveAddr(base, offsets.attack);
	Memory::write(shooting, (BYTE*)&toggle, 1);
}