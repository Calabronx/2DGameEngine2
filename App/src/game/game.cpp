#include "game.h"

#include <map>
#include <iostream>

#include <core/application.h>
#include <core/renderer/renderer.h>
#include <core/renderer/shader.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../stb_image/stb_image.h"

namespace Application
{
	Game::Game()
	{
		// m_BackgroundTexture = Renderer::LoadTexture("textures/grid.png");
	    // m_Shader = Renderer::CreateShader("shaders/sprite.vs", "shaders/sprite.fs");
	    m_SpriteRenderer = std::make_shared<Renderer::SpriteRenderer>();

	    glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
	    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(framebufferSize.x), static_cast<float>(framebufferSize.y), 0.0f, -1.0f, 1.0f);

	    glm::vec2 playerPosition(375, 275);
	    glm::vec2 playerSize(50.0f,35.0f);
	    const float PLAYER_VELOCITY = 0.80f;
		m_PlayerInstance = new Player(playerPosition, playerSize, Renderer::LoadTexture("textures/character.png"), glm::vec3(1.0f) , glm::vec2(PLAYER_VELOCITY));

	    glUseProgram(m_Shader);
	    glUniform1i(glGetUniformLocation(m_Shader, "image"), 0);
	    glUniformMatrix4fv(glGetUniformLocation(m_Shader, "projection"), 1, false, glm::value_ptr(projection));

	    glGetError();
	}

	Game::~Game()
	{
		glDeleteVertexArrays(1, &m_VertexArray);
	    glDeleteBuffers(1, &m_VertexBuffer);
	    glDeleteProgram(m_Shader);
	}

	void Game::OnUpdate(float ts)
	{
		SDL_Event event;
	    std::map<SDL_Keycode, bool> keyMap;
	    while(SDL_PollEvent(&event))
	    {
	        switch(event.type)
	        {
	            case SDL_QUIT:
	                std::cout << "quit" << std::endl;
	                Engine::Application::GetInstance().Stop();
	                break;
	            case SDL_KEYDOWN:
	                keyMap[event.key.keysym.sym] = true;         
	                if (keyMap[SDLK_ESCAPE])
	                    Engine::Application::GetInstance().Stop();
	                if (keyMap[SDLK_a])
	                	m_PlayerInstance->Move(glm::vec2(-5.0f, 0.0f));
	                if (keyMap[SDLK_d])
	                	m_PlayerInstance->Move(glm::vec2(5.0f, 0.0f));
	                if (keyMap[SDLK_s])
	                	m_PlayerInstance->Move(glm::vec2(0.0f, 5.0f));
	                if (keyMap[SDLK_w])
	                	m_PlayerInstance->Move(glm::vec2(0.0f, -5.0f));
	                std::cout << "key down" << std::endl;
	                break;

	        }
	    }
	}

	void Game::OnRender()
	{
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	    glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
	    // m_SpriteRenderer->RenderSprite(m_BackgroundTexture, glm::vec2(0.0f, 0.0f), glm::vec2(framebufferSize.x, framebufferSize.y), 0.0f);
	    m_GameGrid.Render(*m_SpriteRenderer);

	    m_PlayerInstance->RenderObject(*m_SpriteRenderer);
	    glViewport(0, 0, framebufferSize.x, framebufferSize.y);
	    glGetError();
	}
}