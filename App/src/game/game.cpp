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
#include "game_entity_factory.h"
#include "player_input.h"
#include "player_graphics.h"
#include "player_physics.h"
#include <core/input/input.h>
#include "spirit_input.h"
#include "spirit_graphics.h"
#include "spirit_physics.h"

constexpr int INITIAL_X_POS = 375;
constexpr int INITIAL_Y_POS = 275;
constexpr int INITIAL_PLAYER_X_SIZE = 80;
constexpr int INITIAL_PLAYER_Y_SIZE = 55;
constexpr int INITIAL_ENEMY_X_SIZE = 60;
constexpr int INITIAL_ENEMY_Y_SIZE = 55;
constexpr int PLAYER_VELOCITY = 0;

namespace Application
{
	Game::Game()
	{
		// m_BackgroundTexture = Renderer::LoadTexture("textures/grid.png");
	    m_SpriteRenderer = std::make_shared<Renderer::SpriteRenderer>();

	    glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
	    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(framebufferSize.x), static_cast<float>(framebufferSize.y), 0.0f, -1.0f, 1.0f);

	    glm::vec2 playerPosition(INITIAL_X_POS, INITIAL_Y_POS);
	    glm::vec2 playerSize(INITIAL_PLAYER_X_SIZE,INITIAL_PLAYER_Y_SIZE);
	    glm::vec2 enemySize(INITIAL_ENEMY_X_SIZE,INITIAL_ENEMY_Y_SIZE);

	    m_GameWorld = new World(new GameEntityFactory());

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
	    Input::Update();

		std::vector<GameEntity*> entities = m_GameWorld->GetEntities();

		for (auto i = 0; i < entities.size(); ++i)
		{   
			entities[i]->GetInput()->Update(*entities[i], *m_GameWorld);
		}

		// Re-fetch entities after input updates because input handlers may remove
		// entities from the world (which deletes pointers). Using a fresh list
		// prevents processing dangling pointers in the physics step.
		entities = m_GameWorld->GetEntities();

		for (auto i = 0; i < entities.size(); ++i)
		{
			entities[i]->GetPhysics()->Update(*entities[i], *m_GameWorld);
		}

	    if (Input::QuitRequested() || Input::IsKeyPressed(SDL_SCANCODE_ESCAPE))
	    {
	    	Engine::Application::GetInstance().Stop();
	    }

	    m_GameWorld->Update();
	}

	void Game::OnRender()
	{	
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	    glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
	    // m_SpriteRenderer->RenderSprite(m_BackgroundTexture, glm::vec2(0.0f, 0.0f), glm::vec2(framebufferSize.x, framebufferSize.y), 0.0f);

		std::vector<GameEntity*> entities = m_GameWorld->GetEntities();

	    for (auto i = 0; i < entities.size(); ++i)
	    {
			entities[i]->GetGraphics()->Update(*entities[i], *m_SpriteRenderer);
	    }

	    glViewport(0, 0, static_cast<GLint>(framebufferSize.x), static_cast<GLint>(framebufferSize.y));
	    glGetError();
	}

}