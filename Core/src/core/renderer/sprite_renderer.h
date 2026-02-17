#pragma once
#ifndef SPRITE_RENDERER
#define SPRITE_RENDERER

#include "shader.h"
#include "renderer.h"

namespace Renderer {
	
	class SpriteRenderer
	{
		public:
			SpriteRenderer();

		private:
			void InitRenderingData();
		public:
			void RenderSprite(Renderer::Texture &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

		private:
			uint32_t 		  	m_VertexArray;
			uint32_t 		  	m_VertexBuffer;
			uint32_t 		  	m_Shader;
	};
}

#endif
