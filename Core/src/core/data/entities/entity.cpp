#include "entity.h"

GameEntity::GameEntity(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	: m_Input(input) , m_Graphics(graphics), m_Physics(physics)
{
}

