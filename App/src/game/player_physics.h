#pragma once
#include "core/physics.h"
#include <core/data/entities/entity.h>
#include <core/world.h>

#include <glm/glm.hpp>

class PlayerPhysicsComponent : public PhysicsComponent 
{
	public:
		PlayerPhysicsComponent();

		void Update(GameEntity& entity, World& world);

		bool IsWalkingRightDirection() const;
		bool IsWalkingLeftDirection() const;
		bool IsWalkingUpDirection() const;
		bool IsWalkingDownDirection() const;
		bool IsIdle() const;

		bool IsTakingDamage() const;
		bool IsCollision(GameEntity& entity1, GameEntity& entity2) const;
		bool IsCollision(glm::vec2 position1, glm::vec2 size1, glm::vec2 position2, glm::vec2 size2)const;

		void SetIdleState(bool state);
		void DecreaseVelocity(GameEntity& entity) { --entity.m_Velocity;};

		

	private:
		bool m_IsIdle;
		bool m_IsWalkingRight;
		bool m_IsWalkingLeft;
		bool m_IsWalkingUp;
		bool m_IsWalkingDown;

		glm::vec2 m_LastPosition;
};

