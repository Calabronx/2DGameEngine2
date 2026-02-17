#ifndef ENGINE_APP_H
#define ENGINE_APP_H

#include <SDL.h>
#include <vector>
#include <memory>
#include <string>
#include <set>
#include <type_traits>
#include <glm/glm.hpp>

#include "window.h"
#include "layer.h"

namespace Engine
{   
    struct ApplicationSpecification
    {
        std::string Name;
        WindowSpecification WindowSpec;
    };

    class Application
    {
        public:
            Application(const ApplicationSpecification& specification = ApplicationSpecification()); 
            ~Application();

        private:
            void Update();
            void Render(); 

        public:
            void Run();
            void Stop();

            template<typename TLayer>
            requires (std::is_base_of_v<Layer, TLayer>)
            void PushLayer() { m_LayerStack.push_back(std::make_unique<TLayer>()); }
            glm::vec2 GetFramebufferSize() const;

            static Application& GetInstance();
            static float GetTime();

        private:
            ApplicationSpecification           m_Specification;
            std::shared_ptr<Window>            m_Window;
            bool                               m_Running = false;

            std::vector<std::unique_ptr<Layer>> m_LayerStack;
    };
}
#endif