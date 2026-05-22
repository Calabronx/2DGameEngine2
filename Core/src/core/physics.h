#pragma once

class GameEntity;
class World;
class PhysicsComponent
{
	public:
		virtual ~PhysicsComponent() {}
		// virtual void Update(GameEntity& entity, World& world) = 0; caso real, cuando la clase defina world
		virtual void Update(GameEntity& entity, World& world) = 0;
};

