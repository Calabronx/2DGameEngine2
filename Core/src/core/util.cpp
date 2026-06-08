#include "util.h"

#include <glm/glm.hpp>

glm::vec2 GetCenter(GameEntity& entity)
{
	float x = entity.m_Position.x;
	float y = entity.m_Position.y;
	int w = entity.m_Size.x;
	int h = entity.m_Size.y;

	float xCenter = x + w / 2.0f;
	float yCenter = y + h / 2.0f;

	return glm::vec2(xCenter, yCenter);
}