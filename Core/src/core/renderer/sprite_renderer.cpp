#include "sprite_renderer.h"
#include "../application.h"

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Renderer {
    
    SpriteRenderer::SpriteRenderer()
    {
    	m_Shader = Renderer::CreateShader("shaders/sprite.vs", "shaders/sprite.fs");
        
        glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(framebufferSize.x), static_cast<float>(framebufferSize.y), 0.0f, -1.0f, 1.0f);

        glUseProgram(m_Shader);
        glUniform1i(glGetUniformLocation(m_Shader, "image"), 0);
        glUniformMatrix4fv(glGetUniformLocation(m_Shader, "projection"), 1, false, glm::value_ptr(projection));

    	InitRenderingData();
    }

    void SpriteRenderer::InitRenderingData()
    {

    	float vertices[] = { 
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 
        
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &m_VertexArray);
        glGenBuffers(1, &m_VertexBuffer);

        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(m_VertexArray);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void SpriteRenderer::RenderSprite(Renderer::Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
    {
    	 Renderer::Render(texture, m_Shader, m_VertexArray, position, size, rotate, color);
    }
}
