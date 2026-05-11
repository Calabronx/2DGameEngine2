#pragma once
#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "keyboard.h"

class GameEntity;
class InputComponent
{

	public:
		virtual ~InputComponent() {}
		virtual void Update(GameEntity& entity) = 0;
};
#endif
