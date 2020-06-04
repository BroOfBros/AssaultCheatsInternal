// A basic triggerbot.
#pragma once
#include "stdafx.h"
#include "Offsets.h"

class Triggerbot {
public:
	Triggerbot(Offsets* offsets);

	void toggle();
	BOOL isEnabled();

	// TODO: improve and add delay
	void execute();

private:
	Offsets* offsets;
	BOOL enabled;
};