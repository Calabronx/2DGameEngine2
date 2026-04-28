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

    float quadVertices[] = {
        // positions (NDC)
        -1.0f, -1.0f,
         1.0f, -1.0f,
         1.0f,  1.0f,

        -1.0f, -1.0f,
         1.0f,  1.0f,
        -1.0f,  1.0f
    };

    glGenVertexArrays(1, &m_BVertexArray);
    glGenBuffers(1, &m_BVertexBuffer);

    glBindVertexArray(m_BVertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, m_BVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

TriangleShader::~TriangleShader()
{
    glDeleteVertexArrays(1, &m_VertexArray);
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteVertexArrays(1, &m_BVertexArray);
    glDeleteBuffers(1, &m_BVertexBuffer);
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
    glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();
    float time = Engine::Application::GetTime();
    float deltaTime = (float)time / 1000.0f;
    // background shader
    glDisable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);
    glUseProgram(m_Background_Shader);
    GLint location2 = glGetUniformLocation(m_Background_Shader, "iResolution");
    glUniform3f(location2, framebufferSize.x, framebufferSize.y, 1.0f);
    int bgTimeLoc = glGetUniformLocation(m_Background_Shader, "uTime");
    glUniform1f(bgTimeLoc, deltaTime);

    glBindVertexArray(m_BVertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // triangle shader
    glEnable(GL_DEPTH_TEST);
    glUseProgram(m_Shader);
    GLint location = glGetUniformLocation(m_Shader, "iResolution");
    int timeLoc = glGetUniformLocation(m_Shader, "iTime");
    glUniform1f(timeLoc, deltaTime);
    glUniform3f(location, framebufferSize.x, framebufferSize.y, 1.0f);
    glViewport(0, 0, framebufferSize.x, framebufferSize.y);
    
    glBindVertexArray(m_VertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
