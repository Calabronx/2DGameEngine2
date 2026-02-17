#include "TriangleShader.h"
#include <SDL.h>
#include <core/renderer/shader.h>
#include <map>
#include <iostream>
#include <core/application.h>

TriangleShader::TriangleShader()
{
    m_Shader = Renderer::CreateShader("shaders/triangle_shader.vs", "shaders/triangle_shader.fs");
    m_Background_Shader = Renderer::CreateShader("shaders/background_random_color.vs", "shaders/background_random_color.fs");

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    glGenVertexArrays(1, &m_VertexArray);
    glGenBuffers(1, &m_VertexBuffer);

    glBindVertexArray(m_VertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TriangleShader::~TriangleShader()
{
    glDeleteVertexArrays(1, &m_VertexArray);
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteProgram(m_Shader);
    glDeleteProgram(m_Background_Shader);
}

void TriangleShader::OnUpdate(float ts)
{
    SDL_Event event;
    std::map<SDL_Keycode, bool> keyMap;
    // std::cout << "App Layer OnUpdate()" << std::endl;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
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

void TriangleShader::OnRender()
{
    glUseProgram(m_Shader);
    // glUseProgram(m_Background_Shader);

    float time = Engine::Application::GetTime();
    float deltaTime = (float)time / 1000.0f;
    int timeLoc = glGetUniformLocation(m_Shader, "iTime");
    glUniform1f(timeLoc, deltaTime);
    GLint location = glGetUniformLocation(m_Shader, "iResolution");

    glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();

    glUniform3f(location, framebufferSize.x, framebufferSize.y, 1.0f);
    glViewport(0, 0, framebufferSize.x, framebufferSize.y);
    
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_VertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
