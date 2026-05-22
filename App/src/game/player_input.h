#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <core/input/input_component.h>
#include <core/data/entities/entity.h>
#include <glm/glm.hpp>
#include <vector>


	class PlayerInputComponent : public InputComponent
	{
		public:
			PlayerInputComponent();
			virtual void Update(GameEntity& entity, World& world);

			// void 		 MovePlayer(GameEntity& entity, glm::vec2 position);

			void SetDirection();
			void MoveGridPosition(GameEntity& entity, std::vector<std::vector<uint32_t>> &grid, int index);

		private:
			static const int WALK_ACCELERATION = 3;

	};	
#endif

