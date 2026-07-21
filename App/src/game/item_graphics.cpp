#include "item_graphics.h"

ItemGraphicsComponent::ItemGraphicsComponent(ItemPhysicsComponent* physics)
{
    m_Physics = physics;
	m_Sprite.texture = Renderer::LoadTexture("textures/torch_1.png");
}

void ItemGraphicsComponent::Update(GameEntity& entity, Renderer::SpriteRenderer& renderer)
{
	renderer.RenderSprite(m_Sprite.texture,
                          entity.m_Position,
                          entity.m_Size,
                          entity.m_Rotation,
                          entity.m_Color);
}
