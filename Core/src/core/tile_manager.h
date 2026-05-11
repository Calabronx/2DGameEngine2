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
			TileManager();

		public:
			
			void Render(Renderer::SpriteRenderer& renderer);
			// void LoadFile(...);

		private:
			void GenerateTileBoard(const uint32_t boardWidth, const uint32_t boardHeight);
			GameEntity* CreateTile();



		private:
			std::vector<GameObject> m_Tiles;
			std::vector<GameEntity*> m_TilesEntities;
	};
}

#endif
