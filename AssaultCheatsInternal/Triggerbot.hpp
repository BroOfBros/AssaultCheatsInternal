// A basic triggerbot.
#pragma once
#include "stdafx.h"
#include "Offsets.h"

class Triggerbot {
public:
	Triggerbot(Offsets* offsets);

	void execute();

private:
	Offsets* offsets;
};