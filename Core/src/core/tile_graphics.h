#pragma once
#include "renderer/graphics.h"
#include "tile_physics.h"
class TileGraphicsComponent : public GraphicsComponent
{
	public:
		TileGraphicsComponent(TilePhysicsComponent* physics);

		virtual void Update(GameEntity& entity, Renderer::SpriteRenderer& renderer);

	private:
		TilePhysicsComponent *m_TilePhysics;
};

