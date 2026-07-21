#pragma once

#include <core/renderer/graphics.h>
#include <core/renderer/sprite_renderer.h>
#include <core/data/entities/entity.h>
#include "item_physics.h"

class ItemGraphicsComponent : public GraphicsComponent
{
	public:
        ItemGraphicsComponent(ItemPhysicsComponent* physics);

        void Update(GameEntity& entity, Renderer::SpriteRenderer& renderer);

    private:
        Renderer::Sprite        m_Sprite;
        ItemPhysicsComponent* m_Physics;
};

