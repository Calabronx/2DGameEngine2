#pragma once
#include "core/data/entities/ientity_factory.h"

class GameEntityFactory : public IEntityFactory
{
	public:
		GameEntity* CreatePlayer() override;
		GameEntity* CreateEnemy() override;
};

