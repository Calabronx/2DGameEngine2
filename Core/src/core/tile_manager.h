#pragma once
#ifndef TILE_MANAGER
#define TILE_MANAGER

#include <vector>
#include "renderer/sprite_renderer.h"


class GameEntity;
namespace Engine {

	class TileManager
	{
		public:
							TileManager(std::vector<std::vector<uint32_t>> *tileGrid);

		public:
			GameEntity* 	CreateTile(Renderer::Texture tile);
			void 			GenerateTileBoard(std::vector<GameEntity*> &entities, const uint32_t boardWidth, const uint32_t boardHeight);

		private:
			std::vector<std::vector<uint32_t>> *m_TileGrid;
	};
}

#endif
