#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

namespace Input
{
	void Update();

	bool IsKeyPressed(SDL_Scancode key);

	bool QuitRequested();
};

#endif


