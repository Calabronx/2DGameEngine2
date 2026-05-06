#pragma once
#ifndef GRAPHICS_COMPONENT_H
#define GRAPHICS_COMPONENT_H
#include "sprite_renderer.h"

class GameEntity;
class GraphicsComponent
{
	public:
		virtual ~GraphicsComponent() {}
		virtual void Update(GameEntity& entity, Renderer::SpriteRenderer& renderer) = 0;
};

#endif 
