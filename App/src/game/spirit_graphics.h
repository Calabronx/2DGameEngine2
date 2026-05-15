#pragma once

#include <core/renderer/graphics.h>
#include <core/renderer/sprite_renderer.h>
#include <core/data/entities/entity.h>
#include "spirit_physics.h"
class SpiritGraphicsComponent : public GraphicsComponent
{
    public:
        SpiritGraphicsComponent(SpiritPhysicsComponent* physics);

        void Update(GameEntity& entity, Renderer::SpriteRenderer& renderer);

    private:
        Renderer::Sprite        m_Sprite;
        SpiritPhysicsComponent* m_Physics;
};

