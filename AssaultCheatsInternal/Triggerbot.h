// A basic triggerbot.

#pragma once

#include"stdafx.h"
#include "Aim.h"

class Triggerbot {
public:
	Triggerbot(DWORD playersList, DWORD playersCount, tInCross inCross);
	~Triggerbot();

	BOOL isEnabled();
	void enable();
	void disable();

	void execute();

private:
	BOOL enabled;

	DWORD playersList;
	int playersCount;
	tInCross inCross;
};