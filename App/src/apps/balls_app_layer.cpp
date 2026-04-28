#include "balls_app_layer.h"

#include <iostream>
#include <map>
#include <core/application.h>
#include <core/renderer/renderer.h>
#include <core/renderer/shader.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../stb_image/stb_image.h"

/**
 * //TODO
 * Objetivo: desarrollar juego de gemas, estrategia, el jugador tiene que rotar gemas y diamantes,
 * matchear lineas horizontales y verticales de 3 o 4 o mas
 * al matchear una linea las gemas deben destruirse y deben caer las de arriba tipo efecto cascada (creando nuevas)
 * si matchean 4, se destruyen las tres y la cuarta se convierte en una gema especial
 * 
 * 
 * Refencia del juego Bejeweld 3
 * 
 * 
 *  
*/ 


BallsAppLayer::BallsAppLayer()
{   
    m_BackgroundTexture = Renderer::LoadTexture("textures/grid.png");

    // m_Shader = Renderer::CreateShader("shaders/sprite.vs", "shaders/sprite.fs");
    m_SpriteRenderer = std::make_shared<Renderer::SpriteRenderer>();

    glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(framebufferSize.x), static_cast<float>(framebufferSize.y), 0.0f, -1.0f, 1.0f);

    glUseProgram(m_Shader);
    glUniform1i(glGetUniformLocation(m_Shader, "image"), 0);
    glUniformMatrix4fv(glGetUniformLocation(m_Shader, "projection"), 1, false, glm::value_ptr(projection));

    glGetError();

}

BallsAppLayer::~BallsAppLayer()
{
    glDeleteVertexArrays(1, &m_VertexArray);
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteProgram(m_Shader);
}

void BallsAppLayer::OnUpdate(float ts)
{
    SDL_Event event;
    std::map<SDL_Keycode, bool> keyMap;
    // std::cout << "App Layer OnUpdate()" << std::endl;
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
                std::cout << "key down" << std::endl;
                break;
        }
    }

}

void BallsAppLayer::OnRender()
{
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
    m_SpriteRenderer->RenderSprite(m_BackgroundTexture, glm::vec2(0.0f, 0.0f), glm::vec2(framebufferSize.x, framebufferSize.y), 0.0f);
    m_Board.Render(*m_SpriteRenderer);
    glViewport(0, 0, framebufferSize.x, framebufferSize.y);
    glGetError();
}

