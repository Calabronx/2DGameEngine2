#pragma once
#ifndef INPUT_H
#define INPUT_H

#include "../data/entities/entity.h"
#include "keyboard.h"

class InputComponent
{

	public:
		virtual ~InputComponent() {}
		virtual void Update(GameEntity& entity, KeyDirection::Direction direction) = 0;
};
#endif
