#include "entity.h"

GameEntity::GameEntity()
{
}

GameEntity::GameEntity(InputComponent* input, PhysicsComponent* physics, GraphicsComponent* graphics)
	: m_Input(input) , m_Graphics(graphics), m_Physics(physics)
{

}

void GameEntity::Update(Renderer::SpriteRenderer& renderer)
{
	m_Input->Update(*this);
	m_Graphics->Update(*this,renderer);
}
