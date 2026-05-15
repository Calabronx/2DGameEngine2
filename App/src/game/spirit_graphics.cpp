#include "spirit_graphics.h"
#include <core/renderer/renderer.h>

SpiritGraphicsComponent::SpiritGraphicsComponent(SpiritPhysicsComponent* physics)
	: m_Physics(physics)
{
	m_Sprite.texture = Renderer::LoadTexture("textures/spirit2.png");
}

void SpiritGraphicsComponent::Update(GameEntity& entity, Renderer::SpriteRenderer& renderer)
{
	Renderer::Sprite* sprite = new Renderer::Sprite();

	//condiciones de estado
	sprite = &m_Sprite;

	renderer.RenderSprite(sprite->texture,
	 					  entity.m_Position,
	  					  entity.m_Size,
	   					  entity.m_Rotation,
	    				  entity.m_Color);
}
