#pragma once
#include "core/physics.h"
#include <core/data/entities/entity.h>

#include <glm/glm.hpp>

class PlayerPhysicsComponent : public PhysicsComponent 
{
	public:
		PlayerPhysicsComponent();

		virtual void Update(GameEntity& entity);

		bool IsWalkingRightDirection() const;
		bool IsWalkingLeftDirection() const;
		bool IsWalkingUpDirection() const;
		bool IsWalkingDownDirection() const;
		bool IsIdle() const;

		bool IsTakingDamage() const;
		bool IsCollision(GameEntity& entity1, GameEntity& entity2) const;

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

