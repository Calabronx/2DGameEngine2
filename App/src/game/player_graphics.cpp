#include "player_graphics.h"


PlayerGraphicsComponent::PlayerGraphicsComponent(PlayerPhysicsComponent* physics)
	: m_PlayerPhysics(physics)
{
}

void PlayerGraphicsComponent::Update(GameEntity& entity, Renderer::SpriteRenderer& renderer)
{
	Renderer::Sprite* sprite;
	if (m_PlayerPhysics->IsWalkingRightDirection())
	{
		sprite = &m_SpriteWalkRight;
	}
	if (m_PlayerPhysics->IsIdle())
	{
		sprite = &m_SpriteIdle;
	}

	renderer.RenderSprite(sprite.texture, entity.m_Position,entity.m_Size, entity.m_Rotation, entity.m_Color);
}
