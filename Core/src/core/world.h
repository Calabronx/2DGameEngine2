#pragma once
#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "tile_manager.h"
#include "data/entities/ientity_factory.h"

class GameEntity;

struct WorldLimits
{
	glm::vec2 bounds; //left x position and top y position bounds vec
	int windowWidth;
	int windowHeight;
	int row;
	int col;
};

// no me gusta esto ni se usa y eso es una celda, no una grilla de un mundo entero..
struct WorldGrid
{
	int row;
	int col;
};

class World
{
	public:
						World(IEntityFactory* factory);
						~World();

	private:
		void 						InitializeEntities();
	public:
		void						Update(float ts);

		std::vector <GameEntity*> 	GetEntities() { return m_Entities; };
		
		void						AddEntity(GameEntity* entity);
		void						RemoveEntity(GameEntity* entity);
		void 						AddItemToPlayerInventory(GameEntity* item);
		// void 						AddItemToPlayerInventoryWithQuantity(GameEntity* item, std::size_t quantity);
		void 						AddItemToPlayerInventoryWithQuantity(std::size_t quantity);
		void 						RenderWorld();

		void						PlantItemInWorld(unsigned int type, GameEntity* plantTileObjective, int index);
	public:
		WorldLimits					GetWorldLimits() const { return m_WorldBounds; };

		std::vector<std::vector<uint32_t>> GetGridLevel() const { return m_GameLevel; };

		float										m_TimeStep;
	private:
		IEntityFactory								*m_EntityFactory;
		Engine::TileManager 						*m_TileMap;
		std::vector<std::vector<uint32_t>> 			m_GameLevel;// nivel o stage
		std::vector <GameEntity*> 					m_Entities;	// todas las entidades del mundo
		std::vector<GameEntity*>					m_PlayerInventoryVector;
		std::shared_ptr<Renderer::SpriteRenderer> 	m_SpriteRenderer;

		WorldLimits									m_WorldBounds;
		WorldGrid									m_WorldGrid;


		int m_PlayerInventorySlots;
};

#endif
