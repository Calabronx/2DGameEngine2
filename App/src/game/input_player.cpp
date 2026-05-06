#include "input_player.h"
#include <SDL.h>
#include <iostream>
#include <map>

namespace Application
{
	void PlayerInputComponent::Update(GameEntity& entity, KeyDirection::Direction direction)
	{
		switch (direction)
		{
		        case KeyDirection::Direction::DIR_UP:
		            MovePlayer(entity, glm::vec2(-5.0f, 0.0f));
		            break;
				case KeyDirection::Direction::DIR_RIGHT:
		            MovePlayer(entity, glm::vec2(5.0f, 0.0f));
		            break;
				case KeyDirection::Direction::DIR_LEFT:
		            MovePlayer(entity, glm::vec2(0.0f, 5.0f));
		            break;
				case KeyDirection::Direction::DIR_DOWN:
		            MovePlayer(entity, glm::vec2(0.0f, -5.0f));
		            break;
		}
	}

	void PlayerInputComponent::MovePlayer(GameEntity& entity, glm::vec2 position)
	{
		entity.m_Position.x += position.x * entity.m_Velocity.x;
		entity.m_Position.y += position.y * entity.m_Velocity.y;

		std::cout << "X: " << entity.m_Position.x << " Y: " << entity.m_Position.y << " " << std::endl;
	}

	void PlayerInputComponent::SetDirection()
	{
	}

}