#pragma once
#ifndef APP_LAYER
#define APP_LAYER

#include <SDL.h>
#include <vector>

#include "core/layer.h"

class AppLayer : public Engine::Layer
{
	public:
		AppLayer();
		virtual ~AppLayer();

		virtual void OnUpdate(float ts) override;
		virtual void OnRender() override;
	private:
		//std::vector<Texture>        m_textures;

		uint32_t m_Shader = 0;
		uint32_t m_VertexArray = 0;
		uint32_t m_VertexBuffer = 0;
};
#endif

