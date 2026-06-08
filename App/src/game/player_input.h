#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <core/input/input_component.h>
#include <core/data/entities/entity.h>
#include "player_physics.h"
#include <glm/glm.hpp>
#include <vector>


	class PlayerInputComponent : public InputComponent
	{
		public:
			PlayerInputComponent(PlayerPhysicsComponent* physics);
			virtual void Update(GameEntity& entity, World& world);

			// void 		 MovePlayer(GameEntity& entity, glm::vec2 position);

			void SetDirection();
			void MoveGridPosition(GameEntity& entity, std::vector<GameEntity*> entities, int index);

		private:
			static const int WALK_ACCELERATION = 3;

			PlayerPhysicsComponent* m_PlayerPhysics;
	};	
#endif

