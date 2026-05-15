#include "tile_manager.h"

#include "tile_input.h"
#include "tile_physics.h"
#include "tile_graphics.h"

#include <glm/glm.hpp>
#include "application.h"

namespace Engine {

	TileManager::TileManager(std::vector<GameEntity*>& entities)
	{
		glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
		GenerateTileBoard(entities, static_cast<uint32_t>(framebufferSize.x), static_cast<uint32_t>(framebufferSize.y));
	}

	void TileManager::GenerateTileBoard(std::vector<GameEntity*> &entities, const uint32_t boardWidth, const uint32_t boardHeight)
	{
		/**
		 * 
		 *  5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 	 
			5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 	 
			4 4 4 4 4 0 0 0 0 0 4 4 4 4 4 	 
			4 1 4 1 4 0 0 1 0 0 4 1 4 1 4 	 
			3 3 3 3 3 0 0 0 0 0 3 3 3 3 3 	 
			3 3 1 3 3 3 3 3 3 3 3 3 1 3 3 	 
			2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 	 
			2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 	
		 * 
		 * 
		 **/ 
		// GRID 8 X 8
		// std::vector<std::vector<uint32_t>> tileData = {
		// 	{3,2,2,1,1,2,2,3},
		// 	{2,2,2,1,1,2,2,2},
		// 	{2,2,1,1,1,1,2,2},
		// 	{2,2,1,1,1,1,2,2},
		// 	{2,2,1,1,1,1,2,2},
		// 	{2,2,1,1,1,1,2,2},
		// 	{2,2,2,2,2,2,2,2},
		// 	{2,2,2,2,2,2,2,2}
		// };

		std::vector<std::vector<uint32_t>> tileData = {
			{1,1,1,1,1,1,1,1},
			{2,2,2,1,1,2,2,1},
			{2,2,1,1,1,1,2,1},
			{2,2,1,1,1,1,2,1},
			{2,2,1,1,1,1,2,1},
			{2,2,4,4,4,3,2,1},
			{2,2,5,5,5,5,5,1},
			{2,2,2,2,2,2,2,1}
		};

		std::size_t height = tileData.size();
		std::size_t width = tileData[0].size();

		float unit_width = boardWidth / static_cast<float>(width);
		float unit_height = boardHeight / static_cast<float>(height);

		for (uint32_t col = 0; col < height; ++col)
		{
			for (uint32_t row = 0; row < width; ++row)
			{
				if (tileData[col][row] >= 1)
				{
					glm::vec3 color = glm::vec3(1.0f);
					if (tileData[col][row] == 2)
						color = glm::vec3(0.2f, 0.6f, 1.0f);
					else if (tileData[col][row] == 3)
						color = glm::vec3(0.0f, 0.7f, 0.0f);

					if (tileData[col][row] == 3)
						color = glm::vec3(0.0f, 0.7f, 0.0f);
					else if (tileData[col][row] == 4)
						color = glm::vec3(0.8f, 0.8f, 0.4f);
					else if (tileData[col][row] == 5)
						color = glm::vec3(1.0f, 0.5f, 0.0f);

					glm::vec2 pos(unit_width * row, unit_height * col);
					glm::vec2 size(unit_width, unit_height);

					
					if (tileData[col][row] == 1)
					{
						GameEntity* entityTile = CreateTile(Renderer::LoadTexture("textures/block.png"));
						entityTile->m_Id = GRASS1;
						entityTile->m_Position = pos;
						entityTile->m_Size = size;
						entityTile->m_Color = color;

						entities.push_back(entityTile);

					} else {
						GameEntity* entityTile = CreateTile(Renderer::LoadTexture("textures/block.png"));
						entityTile->m_Id = GRASS2;
						entityTile->m_Position = pos;
						entityTile->m_Size = size;
						entityTile->m_Color = color;

						entities.push_back(entityTile);
					}
				}
			}
		}
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