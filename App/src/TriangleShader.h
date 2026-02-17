#pragma once

#include "core/layer.h"
#include <cstdint>

class TriangleShader : public Engine::Layer
{
	public:
		TriangleShader();
		virtual ~TriangleShader();

		virtual void OnUpdate(float ts) override;
		virtual void OnRender() override;
	private:

		uint32_t m_Shader = 0;
		uint32_t m_Background_Shader = 0;
		uint32_t m_VertexArray = 0;
		uint32_t m_VertexBuffer = 0;
};
