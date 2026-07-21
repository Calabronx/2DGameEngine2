#pragma once

#include "core/physics.h"
#include <core/data/entities/entity.h>
#include <core/world.h>

#include <glm/glm.hpp>

class ItemPhysicsComponent : public PhysicsComponent 
{
	public:
		ItemPhysicsComponent();

		void Update(GameEntity& entity, World& world);
};

