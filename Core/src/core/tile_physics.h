#pragma once
#include "physics.h"

class TilePhysicsComponent : public PhysicsComponent
{
	public:
		virtual void Update(GameEntity& entity);
};

