#include "player_input.h"
#include <SDL.h>
#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include <core/input/input.h>
#include <core/application.h>

namespace Application
{
	void PlayerInputComponent::Update(GameEntity& entity)
	{
		entity.m_Velocity.x = 0;
    	entity.m_Velocity.y = 0;

    	const float deltaTime = Engine::Application::GetDeltaTime();

		if (Input::IsKeyPressed(SDL_SCANCODE_W))
		{
		    entity.m_Velocity.y -= WALK_ACCELERATION * deltaTime;
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
		    // entity.m_Velocity.y += WALK_ACCELERATION * deltaTime;
			// std::cout << "mouse moved or pressed "<< std::endl;
			
		}

		// glm::vec2 cursorPos = Input::GetCursorPosition();
        // std::cout << "mouse x: " << cursorPos.x << " mouse y: " << cursorPos.y << std::endl;

		// std::cout << "velocity player X: " << entity.m_Velocity.x << " Y: " << entity.m_Velocity.y << " " << std::endl;
	}

	void PlayerInputComponent::SetDirection()
	{
	}

}