#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "tile_manager.h"
#include "data/entities/ientity_factory.h"

class GameEntity;
class World
{
	public:
						World(IEntityFactory* factory);
						~World();

	private:
		void 						InitializeEntities();
	public:
		std::vector <GameEntity*> 	GetEntities() { return m_Entities; };
		
		void						AddEntity(GameEntity* entity);
		void 						RenderWorld();
	
	private:
		IEntityFactory							*m_EntityFactory;
		std::vector<std::vector<uint32_t>> 		m_GameGrid;
		Engine::TileManager 					*m_TileMap;
		std::vector <GameEntity*> 				m_Entities;

};

#endif
