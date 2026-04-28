#pragma once
#ifndef AUDIO_APP_LAYER
#define AUDIO_APP_LAYER

#include <SDL.h>
#include <vector>
#include <memory>

#include "core/layer.h"
#include <core/renderer/renderer.h>
#include <core/renderer/sprite_renderer.h>

class AudioVisualApp : public Engine::Layer
{
	public:
		AudioVisualApp();
		virtual ~AudioVisualApp();

		virtual void OnUpdate(float ts) override;
		virtual void OnRender() override;

	private:
		std::shared_ptr<Renderer::SpriteRenderer>	m_SpriteRenderer;
		Renderer::Texture			m_BackgroundTexture;

		uint32_t					m_Shader = 0;
		uint32_t					m_VertexArray = 0;
		uint32_t 					m_VertexBuffer = 0;
		uint32_t 					m_ElementBuffer = 0;
};
#endif

