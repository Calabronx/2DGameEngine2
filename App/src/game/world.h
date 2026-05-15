#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <core/data/entities/entity.h>
#include <core/tile_manager.h>

class World
{
	public:
						World();
						~World();

	private:
		void 			InitializeEntities();

		GameEntity* 	CreatePlayer();
		GameEntity* 	CreateEnemy();

	public:
		std::vector <GameEntity*> 		m_Entities;
		Engine::TileManager 			*m_GameGrid;
		
	private:

};

#endif
