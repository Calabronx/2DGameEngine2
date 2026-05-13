#pragma once

#include <core/renderer/graphics.h>
#include <core/renderer/sprite_renderer.h>
#include <core/data/entities/entity.h>
class SpiritGraphicsComponent : public GraphicsComponent
{
public:
    void Update(GameEntity& entity, Renderer::SpriteRenderer* renderer);
};

