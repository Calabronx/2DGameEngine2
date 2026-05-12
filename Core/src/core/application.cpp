#include "application.h"

#include <iostream>
#include <cassert>
#include <map>
#include <glad/glad.h>

namespace Engine {

    static Application* s_Application = nullptr;
    static float s_DeltaTime = 0.0f;

    Engine::Application::Application(const ApplicationSpecification& specification)
        : m_Specification(specification)
    {
        s_Application = this;

        if (m_Specification.WindowSpec.Title.empty())
            m_Specification.WindowSpec.Title = m_Specification.Name;

        m_Window = std::make_shared<Window>(m_Specification.WindowSpec);
        m_Window->CreateWindow();

        m_Window->CreateSurface();

        // Run();
    }

    Application::~Application()
    {
        m_Window->DestroyWindow();
    }

    void Application::Update()
    {
        Render();
        
        // m_Window->Update();
    }

    void Application::Render()
    {
        SDL_GL_SwapWindow(m_Window->GetWindow());
    }

    void Application::Run()
    {
        m_Running = true;
        float lastTime = GetTime();

        while(m_Running)
        {
            // manejar window closing
            float currentTime = GetTime();
            float delta = currentTime - lastTime;

            float timestep = glm::clamp(currentTime - lastTime, 0.001f, 0.1f);

            SetDeltaTime(timestep);
            lastTime = currentTime; 

            for (const std::unique_ptr<Layer>& layer : m_LayerStack)
            {
                layer->OnUpdate(timestep);
            }

            for (const std::unique_ptr<Layer>& layer : m_LayerStack)
            {
                layer->OnRender();
            }


            Update();

        }
    }

    glm::vec2 Application::GetFramebufferSize() const
    {
        return m_Window->GetFramebufferSize();
    }

    void Application::Stop()
    {
        m_Running = false;
    }

    Application& Application::GetInstance()
    {
        assert(s_Application);
        return *s_Application;
    }

    float Application::GetTime()
    {
        return (float) SDL_GetTicks();
    }

    void Application::SetDeltaTime(float time)
    {
		s_DeltaTime = time;
    }

    float Application::GetDeltaTime()
    {
        return s_DeltaTime;
    }
}
