#include "tile_manager.h"

#include "tile_input.h"
#include "tile_physics.h"
#include "tile_graphics.h"

#include <glm/glm.hpp>
#include "application.h"

namespace Engine {
	constexpr int ROW_CENTER = 110;
	constexpr int COL_CENTER = 75;

	TileManager::TileManager(std::vector<std::vector<uint32_t>>* level)
	{
		m_TileLevel = level;
	}
	std::vector<GameEntity*> TileManager::GenerateTileBoard(const uint32_t boardWidth, const uint32_t boardHeight)
	{
		std::vector<GameEntity*> tilesEntities;
		std::vector<std::vector<uint32_t>> &tileLevelData = *m_TileLevel;

		std::size_t height = tileLevelData.size();
		std::size_t width = tileLevelData[0].size();

		float unit_width = boardWidth / static_cast<float>(width);
		float unit_height = boardHeight / static_cast<float>(height);

		for (uint32_t col = 0; col < height; ++col)
		{
			for (uint32_t row = 0; row < width; ++row)
			{
				if (tileLevelData[col][row] >= 1)
				{
					glm::vec3 color = glm::vec3(1.0f);
					if (tileLevelData[col][row] == 2)
						color = glm::vec3(0.2f, 0.6f, 1.0f);
					else if (tileLevelData[col][row] == 3)
						color = glm::vec3(0.0f, 0.7f, 0.0f);

					if (tileLevelData[col][row] == 3)
						color = glm::vec3(0.0f, 0.7f, 0.0f);
					else if (tileLevelData[col][row] == 4)
						color = glm::vec3(0.8f, 0.8f, 0.4f);
					else if (tileLevelData[col][row] == 5)
						color = glm::vec3(1.0f, 0.5f, 0.0f);

					glm::vec2 pos(unit_width * row, unit_height * col);
					glm::vec2 size(unit_width, unit_height);

					if (tileLevelData[col][row] == 1)
					{
						GameEntity* entityTile = CreateTile(Renderer::LoadTexture("textures/block.png"));
						entityTile->m_Id = GRASS1;
						entityTile->m_CellGrid.row = row;
						entityTile->m_CellGrid.col = col;
						entityTile->m_Position = pos;
						entityTile->m_Size = size;
						entityTile->m_Color = color;

						tilesEntities.push_back(entityTile);
					} else {
						GameEntity* entityTile = CreateTile(Renderer::LoadTexture("textures/block.png"));
						entityTile->m_Id = GRASS2;
						entityTile->m_CellGrid.row = row;
						entityTile->m_CellGrid.col = col;
						entityTile->m_TileIndex = col;
						entityTile->m_Position = pos;
						entityTile->m_Size = size;
						entityTile->m_Color = color;

						tilesEntities.push_back(entityTile);
					}
				}
			}
		}
		return tilesEntities;
	}

	GameEntity* TileManager::CreateTile(Renderer::Texture tile)
	{
		TileInputComponent *input = new TileInputComponent();
		TilePhysicsComponent *physics = new TilePhysicsComponent();
		TileGraphicsComponent *graphics = new TileGraphicsComponent(physics, tile);

		return new GameEntity(input,
							  physics,
							  graphics);
	}
}