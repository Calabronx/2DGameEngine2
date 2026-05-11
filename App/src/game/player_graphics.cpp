#include "player_graphics.h"


PlayerGraphicsComponent::PlayerGraphicsComponent(PlayerPhysicsComponent* physics)
	: m_PlayerPhysics(physics)
{
	m_SpriteIdle.texture = Renderer::LoadTexture("textures/encapuchado_frente_1.png");
	m_SpriteWalkUp.texture = Renderer::LoadTexture("textures/encapuchado_detras_1.png");
	m_SpriteWalkLeft.texture = Renderer::LoadTexture("textures/encapuchado_izq_1.png");
}

void PlayerGraphicsComponent::Update(GameEntity& entity, Renderer::SpriteRenderer& renderer)
{
	Renderer::Sprite* sprite = new Renderer::Sprite();
	if (m_PlayerPhysics->IsWalkingUpDirection())
	{
		sprite = &m_SpriteWalkUp;
	}
	else if (m_PlayerPhysics->IsWalkingDownDirection() || m_PlayerPhysics->IsWalkingRightDirection())
	{
		sprite = &m_SpriteIdle;
	}
	else if (m_PlayerPhysics->IsWalkingLeftDirection())
	{
		sprite = &m_SpriteWalkLeft;
	} else if (m_PlayerPhysics->IsIdle())
	{
		sprite = &m_SpriteIdle;
	}
	renderer.RenderSprite(sprite->texture,
	 					  entity.m_Position,
	  					  entity.m_Size,
	   					  entity.m_Rotation,
	    				  entity.m_Color);
}
