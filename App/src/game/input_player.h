#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <core/input/input_component.h>
#include <core/input/keyboard.h>
#include <glm/glm.hpp>
#include <core/data/entities/entity.h>

namespace Application
{
	class PlayerInputComponent : public InputComponent
	{
	public:
		virtual void Update(GameEntity& entity, KeyDirection::Direction direction);

		void 		 MovePlayer(GameEntity& entity, glm::vec2 position);

		void SetDirection();

	};
};
#endif

