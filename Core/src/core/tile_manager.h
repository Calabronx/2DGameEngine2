#pragma once
#ifndef TILE_MANAGER
#define TILE_MANAGER

#include <vector>
#include "renderer/sprite_renderer.h"
#include "game_object.h"
#include "data/entities/entity.h"

namespace Engine {

	class TileManager
	{
		public:
			TileManager(std::vector<GameEntity*> &entities);

		public:
			
			// void Render(Renderer::SpriteRenderer& renderer);
			// void LoadFile(...);

			GameEntity* CreateTile(Renderer::Texture tile);
		private:
			void GenerateTileBoard(std::vector<GameEntity*> &entities, const uint32_t boardWidth, const uint32_t boardHeight);

		private:
			// std::vector<GameEntity*> m_Entities;
	};
}

#endif
