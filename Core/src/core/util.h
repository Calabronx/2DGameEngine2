#ifndef UTIL_H
#define UTIL_H
#include <glm/glm.hpp>
#include "data/entities/entity.h"

bool HasCollision(glm::vec2 position1, glm::vec2 size1, 
	glm::vec2 position2, glm::vec2 size2);

glm::vec2 GetCenter(GameEntity& entity);

#endif


