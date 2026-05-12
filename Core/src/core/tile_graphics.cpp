#include "tile_graphics.h"

TileGraphicsComponent::TileGraphicsComponent(TilePhysicsComponent* physics, Renderer::Texture tile)
{
    m_Tile = tile;
}

void TileGraphicsComponent::Update(GameEntity& entity, Renderer::SpriteRenderer& renderer)
{
}
