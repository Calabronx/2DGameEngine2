#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>
#include <glm/glm.hpp>

namespace Input
{
	void Update();

	bool IsKeyPressed(SDL_Scancode key);

	bool IsMousePressed();

	glm::vec2 GetCursorPosition();

	bool QuitRequested();
};

#endif


