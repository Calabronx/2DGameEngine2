#include "tile_manager.h"

#include "renderer/renderer.h"
#include <glm/glm.hpp>
#include "application.h"

namespace Engine {

	TileManager::TileManager()
	{
		glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
		GenerateTileBoard(framebufferSize.x, framebufferSize.y);
	}

	void TileManager::GenerateTileBoard(const uint32_t boardWidth, const uint32_t boardHeight)
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
		std::vector<std::vector<uint32_t>> tileData = {
			{5,5,5,5,5,5,5,5},
			{5,5,5,5,5,5,5,5},
			{4,4,4,4,0,0,0,0},
			{4,1,4,1,4,2,2,1},
			{3,3,3,3,3,3,3,3},
			{3,3,3,3,3,1,3,3},
			{2,2,2,2,2,2,2,2},
			{2,2,2,2,2,2,2,2}
		};

		uint32_t height = tileData.size();
		uint32_t width = tileData[0].size();

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
					else if (tileData[col][row] == 4)
						color = glm::vec3(0.8f, 0.8f, 0.4f);
					else if (tileData[col][row] == 5)
						color = glm::vec3(1.0f, 0.5f, 0.0f);

					glm::vec2 pos(unit_width * row, unit_height * col);
					glm::vec2 size(unit_width, unit_height);

					m_Tiles.push_back(GameObject(pos, size, tileData[col][row] == 2 ? Renderer::LoadTexture("textures/gema.png") 
						: tileData[col][row] == 5 ? Renderer::LoadTexture("textures/gema_roja.png") : Renderer::LoadTexture("textures/gema_verde.png"), color));

					// m_Tiles.push_back(GameObject(pos, size, Renderer::LoadTexture("textures/block.png") , color));
				}
			}
		}

	}

	void TileManager::Render(Renderer::SpriteRenderer& renderer)
	{
		for (GameObject& tile : m_Tiles)
		{
			if (!tile.IsDestroyed())
				tile.RenderObject(renderer);
		}
	}

}