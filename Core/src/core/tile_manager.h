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
							TileManager(std::vector<std::vector<uint32_t>> *level);

		public:
			GameEntity* 						CreateTile(Renderer::Texture tile);
			std::vector<GameEntity*> 			GenerateTileBoard(const uint32_t boardWidth, const uint32_t boardHeight);

		private:
			// capaz puede ser un struct de nivel
			std::vector<std::vector<uint32_t>> *m_TileLevel;
	};
}

#endif
