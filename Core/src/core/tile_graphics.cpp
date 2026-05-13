#include "tile_graphics.h"

TileGraphicsComponent::TileGraphicsComponent(TilePhysicsComponent* physics, Renderer::Texture tile)
{
    m_TilePhysics = physics;
    m_Tile = tile;
}

void TileGraphicsComponent::Update(GameEntity& entity, Renderer::SpriteRenderer& renderer)
{
    renderer.RenderSprite(m_Tile,
                          entity.m_Position,
                          entity.m_Size,
                          entity.m_Rotation,
                          entity.m_Color);
}
