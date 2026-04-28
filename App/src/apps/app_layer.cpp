#include "app_layer.h"

#include <iostream>
#include <map>
#include <core/application.h>
#include <core/renderer/renderer.h>
#include <core/renderer/shader.h>
#include <glad/glad.h>

AppLayer::AppLayer()
{   

    m_Shader = Renderer::CreateShader("shaders/triangle.vs", "shaders/triangle.fs");

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

AppLayer::~AppLayer()
{
    glDeleteVertexArrays(1, &m_VertexArray);
    glDeleteBuffers(1, &m_VertexBuffer);
    glDeleteProgram(m_Shader);
}

void AppLayer::OnUpdate(float ts)
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

void AppLayer::OnRender()
{
    glUseProgram(m_Shader);

    float time = Engine::Application::GetTime();
    int timeLoc = glGetUniformLocation(m_Shader, "uTime");
    glUniform1f(timeLoc, time);
    
    glm::vec2 framebufferSize = Engine::Application::GetInstance().GetFramebufferSize();

    glViewport(0, 0, framebufferSize.x, framebufferSize.y);
    
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glBindVertexArray(m_VertexArray);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
