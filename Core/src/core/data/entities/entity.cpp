#include "entity.h"

GameEntity::GameEntity(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	: m_Input(input) 
	, m_Graphics(graphics)
	, m_Physics(physics)
	, m_EntityLifeCounter(0)
{
}

GameEntity::~GameEntity()
{
	if (m_Input) delete m_Input; m_Input = nullptr;
	if (m_Graphics) delete m_Graphics; m_Graphics = nullptr;
	if (m_Physics) delete m_Physics; m_Physics = nullptr;
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

glm::vec2 GameEntity::GetCenter() const
{
	float x = m_Position.x;
	float y = m_Position.y;
	int w = m_Size.x;
	int h = m_Size.y;

	float xCenter = x + w / 2.0f;
	float yCenter = y + h / 2.0f;

	return glm::vec2(xCenter, yCenter);
}