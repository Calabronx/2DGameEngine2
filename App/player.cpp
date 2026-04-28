#include "player.h"
#include <iostream>


Application::Player::Player(glm::vec2 pos, glm::vec2 size, Renderer::Texture sprite, glm::vec3 color, glm::vec2 velocity)
	: GameObject(pos, size, sprite, color, velocity)
{
}

void Application::Player::Move(glm::vec2 position)
{
	m_Position.x += position.x * m_Velocity.x;
	m_Position.y += position.y * m_Velocity.y;

	std::cout << "X: " << m_Position.x << " Y: " << m_Position.y << " " << std::endl;
}
