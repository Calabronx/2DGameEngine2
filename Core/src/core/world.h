#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <glm/glm.hpp>

#include "tile_manager.h"
#include "data/entities/ientity_factory.h"

class GameEntity;

struct WorldLimits
{
	glm::vec2 bounds; //left x position and top y position bounds vec
	int width;
	int height;
};

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
	public:
		WorldLimits					GetWorldLimits() const { return m_WorldBounds; };

		std::vector<std::vector<uint32_t>> GetGridLevel() const { return m_GameLevel; };

	private:
		IEntityFactory							*m_EntityFactory;
		Engine::TileManager 					*m_TileMap;
		std::vector<std::vector<uint32_t>> 		m_GameLevel;// nivel o stage
		std::vector <GameEntity*> 				m_Entities;	// todas las entidades del mundo
		std::vector <GameEntity*> 				m_GridTiles;	// todas las tiles del mundo, ej

		WorldLimits								m_WorldBounds;

};

#endif
