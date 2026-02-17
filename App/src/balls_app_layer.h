#pragma once
#ifndef BALL_APP_LAYER
#define BALL_APP_LAYER

#include <SDL.h>
#include <vector>
#include <memory>

#include "core/layer.h"
#include <core/renderer/renderer.h>
#include <core/renderer/sprite_renderer.h>
#include <core/tile_manager.h>

class BallsAppLayer : public Engine::Layer
{
	public:
		BallsAppLayer();
		virtual ~BallsAppLayer();

		virtual void OnUpdate(float ts) override;
		virtual void OnRender() override;

	private:
		std::shared_ptr<Renderer::SpriteRenderer>	m_SpriteRenderer;
		Renderer::Texture			m_BackgroundTexture;
		Engine::TileManager 		m_Board;

		uint32_t					m_Shader = 0;
		uint32_t					m_VertexArray = 0;
		uint32_t 					m_VertexBuffer = 0;
		uint32_t 					m_ElementBuffer = 0;
};
#endif

