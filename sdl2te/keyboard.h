#pragma once
#include "player.h"

struct keyboard
{
	int* keyS;
	const Uint8* returnKeyState()
	{
		return SDL_GetKeyboardState(keyS);
	}
};