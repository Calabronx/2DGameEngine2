#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <core/input/input_component.h>
#include <core/data/entities/entity.h>
#include "player_physics.h"
#include <glm/glm.hpp>
#include <vector>

	struct TargetCell
	{
		glm::vec2 targetPosition;
		glm::vec2 targetSize;
		glm::vec2 targetCenter;
		glm::ivec2 gridPosition;
		bool isTarget = false;
		uint32_t targetIDSelf;
	};

	struct PlayerInventory
	{
		std::vector<GameEntity*> Items;
		std::size_t				 Size;
	};

	class PlayerInputComponent : public InputComponent
	{
		public:
			PlayerInputComponent(PlayerPhysicsComponent* physics);
			virtual void Update(GameEntity& entity, World& world);

			// void 		 MovePlayer(GameEntity& entity, glm::vec2 position);
			void SetDirection();
			void GetMovementCells(World& world, TargetCell& target);
			void MoveGridPosition(GameEntity& entity, std::vector<GameEntity*> entities, int index);
			void PlantItem(World& world, GameEntityType Itemtype, GameEntity* plantTileObjective);
			void RemoveItemFromGround(World& world, GameEntity* item);

		private:
			static const int WALK_ACCELERATION = 3;

			PlayerPhysicsComponent* m_PlayerPhysics;
			PlayerInventory			m_PlayerInventory;
	};	
#endif

