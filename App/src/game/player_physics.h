#pragma once
#include "core/physics.h"

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

	private:
		bool m_IsWalkingRight;
		bool m_IsWalkingLeft;
		bool m_IsWalkingUp;
		bool m_IsWalkingDown;
};

