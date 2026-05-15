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

	    m_GameGrid = new Engine::TileManager(m_Entities);

	    GameEntity *Player = CreatePlayer();

	    Player->m_Id = PLAYER;
	    Player->m_Position = playerPosition;
	    Player->m_Size = playerSize;
	    Player->m_Velocity = glm::vec2(PLAYER_VELOCITY);
	    Player->m_Color = glm::vec3(1.0f);

	    m_Entities.push_back(Player);

	    // posiciones a ubicar las entidades
	    std::vector<glm::vec2> enemyPositions = {
	    	glm::vec2(22.382f, 29.1355f),
	    	glm::vec2(339.393f, 13.6976f),
	    	glm::vec2(708.326, 13.6976f),
	    	glm::vec2(708.326, 309.459f),
	    	glm::vec2(721.443f, 547.423f),
	    	glm::vec2(326.427f, 547.423f),
	    	glm::vec2(28.486f, 547.423f),
	    };
	    const int spiritsSize = enemyPositions.size();

	    for (auto i = 0; i < spiritsSize;++i)
	    {
	    	GameEntity *Spirit = CreateEnemy();

	    	Spirit->m_Id = SPIRIT;
	    	Spirit->m_Position = enemyPositions[i];
		    // Spirit->m_Size = playerSize; // por ahora le mandamos el mismo tamaño del jugador
		    Spirit->m_Size = enemySize; // por ahora le mandamos el mismo tamaño del jugador
		    Spirit->m_Velocity = glm::vec2(PLAYER_VELOCITY); // misma velocidad que el jugador
		    Spirit->m_Color = glm::vec3(1.0f); // a definir, podria cambiar el color de una textura de espiritu
		    m_Entities.push_back(Spirit);
	    }

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

	    for (auto i = 0; i < m_Entities.size(); ++i)
	    {
	    	m_Entities[i]->GetInput()->Update(*m_Entities[i], *m_Entities);
	    }

	    for (auto i = 0; i < m_Entities.size(); ++i)
	    {
	    	m_Entities[i]->GetPhysics()->Update(*m_Entities[i]);
	    }

	    if (Input::QuitRequested() || Input::IsKeyPressed(SDL_SCANCODE_ESCAPE))
	    {
	    	Engine::Application::GetInstance().Stop();
	    }
	}

	void Game::OnRender()
	{	
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	    glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
	    // m_SpriteRenderer->RenderSprite(m_BackgroundTexture, glm::vec2(0.0f, 0.0f), glm::vec2(framebufferSize.x, framebufferSize.y), 0.0f);

	    for (auto i = 0; i < m_Entities.size(); ++i)
	    {
	    	m_Entities[i]->GetGraphics()->Update(*m_Entities[i], *m_SpriteRenderer);
	    }

	    glViewport(0, 0, static_cast<GLint>(framebufferSize.x), static_cast<GLint>(framebufferSize.y));
	    glGetError();
	}

	GameEntity* Game::CreatePlayer() // aca uso el "patron factory" para crear una entidad de jugador
	{
		PlayerInputComponent	*input	  = new PlayerInputComponent();
		PlayerPhysicsComponent	*physics  = new PlayerPhysicsComponent();
		PlayerGraphicsComponent	*graphics = new PlayerGraphicsComponent(physics);

		return new GameEntity(input,
							  physics,
							  graphics);
	}

	GameEntity* Game::CreateEnemy() // aca uso el "patron factory" para crear una entidad de jugador
	{
		SpiritInputComponent	*input	  = new SpiritInputComponent();
		SpiritPhysicsComponent	*physics  = new SpiritPhysicsComponent();
		SpiritGraphicsComponent	*graphics = new SpiritGraphicsComponent(physics);

		return new GameEntity(input,
							  physics,
							  graphics);
	}

}