#pragma once

class GameEntity;
class IEntityFactory
{
	public:

		virtual GameEntity* CreatePlayer() = 0;
		virtual GameEntity* CreateEnemy() = 0;
		virtual GameEntity* CreateItem() = 0;
		
		virtual ~IEntityFactory() = default;
};