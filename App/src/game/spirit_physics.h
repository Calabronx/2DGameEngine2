#pragma once
#include <core/physics.h>

class SpiritPhysicsComponent : public PhysicsComponent
{
public:
    void Update(GameEntity& entity, World& world);
};

