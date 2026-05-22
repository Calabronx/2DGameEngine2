#pragma once
#ifndef GAME_APP_LAYER
#define GAME_APP_LAYER

#include <memory>
#include <core/layer.h>
#include <core/renderer/renderer.h>
#include <core/renderer/sprite_renderer.h>
#include <core/tile_manager.h>
#include <core/data/entities/entity.h>
#include <cstdint>
#include <vector>

#include "core/world.h"

namespace Application {
	class Game : public Engine::Layer
	{
		public:
			Game();
			virtual ~Game();

			virtual void OnUpdate(float ts) override;
			virtual void OnRender() override;

		private:
			World										*m_GameWorld;
			std::shared_ptr<Renderer::SpriteRenderer> 	m_SpriteRenderer;
			Renderer::Texture 							m_BackgroundTexture;

			uint32_t 	m_Shader = 0;
			uint32_t 	m_VertexArray = 0;
			uint32_t 	m_VertexBuffer = 0;
	};
}
#endif

