#include "player_input.h"
#include <SDL.h>
#include <iostream>
#include <map>
#include <core/input/input.h>
#include <core/application.h>
#include "core/world.h"

	namespace
	{
		int g_tilePosition = 27;

		bool g_firstClick = false;
	};

	PlayerInputComponent::PlayerInputComponent()
	{
	}

	void PlayerInputComponent::Update(GameEntity& entity, World& world)
	{
		entity.m_Velocity.x = 0;
    	entity.m_Velocity.y = 0;

    	const float deltaTime = Engine::Application::GetDeltaTime();

		if (Input::IsKeyPressed(SDL_SCANCODE_W))
		{
		    entity.m_Velocity.y -= WALK_ACCELERATION * deltaTime;
		    // MoveGridPosition(entity, world.GetEntities(), g_tilePosition - 8);
		}

		if (Input::IsKeyPressed(SDL_SCANCODE_D))
		{
		   	entity.m_Velocity.x += WALK_ACCELERATION * deltaTime;
		}

		if (Input::IsKeyPressed(SDL_SCANCODE_A))
		{
		    entity.m_Velocity.x -= WALK_ACCELERATION * deltaTime;
		}

		if (Input::IsKeyPressed(SDL_SCANCODE_S))
		{
		    entity.m_Velocity.y += WALK_ACCELERATION * deltaTime;
		}

		if (Input::IsMousePressed())
		{
		// 	if (g_firstClick)
		// 	{
		// 		return;
		// 	}
		//     // entity.m_Velocity.y += WALK_ACCELERATION * deltaTime;
		// 	// std::cout << "mouse moved or pressed "<< std::endl;
		// 	glm::vec2 cursorPos = Input::GetCursorPosition();
	    //     // std::cout << "mouse x: " << cursorPos.x << " mouse y: " << cursorPos.y << std::endl;
		// 	bool clicked = false;
		// 	for (auto i = 0; i < world.GetEntities().size() && !g_firstClick; i++)
		// 	{
		// 		if(world.GetEntities()[i]->IsSelected(cursorPos)) // movimento del jugador en las tiles, deberia identificar si es una Tile real
		// 		{
	    //     		std::cout << "tile id position : " << i << std::endl;
		// 			// glm::vec2 objective = world.GetEntities()[i]->GetCenter();
		// 			// entity.m_Position = objective - glm::vec2(entity.m_Size.x / 2.0f, entity.m_Size.y / 2.0f); // ubicar al jugador en el centro de la tile
		// 			if (g_tilePosition - 8 == i)
		// 			{
		// 				MoveGridPosition(entity, world.GetEntities(), g_tilePosition - 8);
		// 			} else if (g_tilePosition + 8 == i)
		// 			{
		// 				MoveGridPosition(entity, world.GetEntities(), g_tilePosition + 8);
		// 			} else if (g_tilePosition + 1 == i)
		// 			{
		// 				MoveGridPosition(entity, world.GetEntities(), g_tilePosition + 1);
		// 			} else if (g_tilePosition - 1 == i)
		// 			{
		// 				MoveGridPosition(entity, world.GetEntities(), g_tilePosition - 1);
		// 			}

		// 			g_firstClick = true;
		// 			// std::cout << "jugador toco la entidad: " << world.GetEntities()[i]->m_Id << std::endl;
		// 		}
		// 	}
		} 
		// else
		// {
		// 	g_firstClick = false;
		// }
		// std::cout << "velocity player X: " << entity.m_Velocity.x << " Y: " << entity.m_Velocity.y << " " << std::endl;
	}

	void PlayerInputComponent::SetDirection()
	{
	}

	void PlayerInputComponent::MoveGridPosition(GameEntity& entity, std::vector<GameEntity*> entities, int index)
	{
		if (index > entities.size() - 1)
			return;

		glm::vec2 centerTile = entities[index]->GetCenter();
		g_tilePosition = index;
		entity.m_Position = centerTile - glm::vec2(entity.m_Size.x / 2.0f, entity.m_Size.y / 2.0f);
	}

