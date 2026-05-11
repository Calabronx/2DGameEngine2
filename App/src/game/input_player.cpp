#include "input_player.h"
#include <SDL.h>
#include <iostream>
#include <map>
#include <core/input/input.h>
#include <core/application.h>

namespace Application
{
	void PlayerInputComponent::Update(GameEntity& entity)
	{
		entity.m_Velocity.x = 0;
    	entity.m_Velocity.y = 0;
    	float time = Engine::Application::GetTime();

		if (Input::IsKeyPressed(SDL_SCANCODE_W))
		{
		    entity.m_Velocity.y -= WALK_ACCELERATION * 0.20f;
		}

		if (Input::IsKeyPressed(SDL_SCANCODE_D))
		{
		   	entity.m_Velocity.x += WALK_ACCELERATION * 0.20f;
		}

		if (Input::IsKeyPressed(SDL_SCANCODE_A))
		{
		    entity.m_Velocity.x -= WALK_ACCELERATION * 0.20f;
		}

		if (Input::IsKeyPressed(SDL_SCANCODE_S))
		{
		    entity.m_Velocity.y += WALK_ACCELERATION * 0.20f;
		}

		std::cout << "velocity player X: " << entity.m_Velocity.x << " Y: " << entity.m_Velocity.y << " " << std::endl;
	}

	void PlayerInputComponent::SetDirection()
	{
	}

}