#pragma once
#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "keyboard.h"
#include <vector>

class GameEntity;
class InputComponent
{

	public:
		virtual ~InputComponent() {}
		virtual void Update(GameEntity& entity, std::vector<GameEntity*> entities) = 0;
};
#endif
