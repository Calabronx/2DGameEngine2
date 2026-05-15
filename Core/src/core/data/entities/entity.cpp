#include "entity.h"

GameEntity::GameEntity(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	: m_Input(input) , m_Graphics(graphics), m_Physics(physics)
{
}

bool GameEntity::IsSelected(glm::vec2 mousePos)
{
	float x = m_Position.x;
	float y = m_Position.y;
	int w = m_Size.x;
	int h = m_Size.y;

	bool selected = ((mousePos.x >= x) && (mousePos.x <= x + w))
	&& ((mousePos.y >= y) && (mousePos.y <= y + h));

	return selected;
}