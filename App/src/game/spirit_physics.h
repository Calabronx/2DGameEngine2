#pragma once
#include <core/physics.h>
#include <core/world.h>
#include <core/data/entities/entity.h>

class SpiritPhysicsComponent : public PhysicsComponent
{
public:
    void Update(GameEntity& entity, World& world);
};

