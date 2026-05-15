#include "tile_physics.h"

void TilePhysicsComponent::Update(GameEntity& entity)
{
	m_IsSelected = IsSelected(Input::GetMousePosition());
}

bool TilePhysicsComponent::IsSelected(glm::vec2 mousePos)
{
	float x = m_Position.x;
	float y = m_Position.y;
	int w = m_Size.x;
	int h = m_Size.y;

	bool selected = ((mousePos.x >= x) && (mousePos.x <= x + w))
	&& ((mousePos.y >= y) && (mousePos.y <= y + h));

	return selected;
}