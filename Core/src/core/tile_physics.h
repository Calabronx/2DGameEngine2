#pragma once
#include "physics.h"

class TilePhysicsComponent : public PhysicsComponent
{
	public:
		void Update(GameEntity& entity, World& world);

	private:
		bool m_IsSelected;
};

