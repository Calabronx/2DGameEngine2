#ifndef WINDOW_H
#define WINDOW_H

#include <SDL.h>
#include <glm/glm.hpp>
#include <string>

namespace Engine {

    struct WindowSpecification
    {
        std::string     Title;
        uint32_t        Width;
        uint32_t        Height;
        bool            IsResizable = false; //por ahora no se puede agrandar
        bool            VSync = true;
    };

    class Window
    {
        public:
            Window(const WindowSpecification& specification = WindowSpecification());
            ~Window();

            void CreateWindow();
            void CreateSurface();
            void DestroyWindow();
            void DestroySurface();

            bool ShouldClose() const;

            void Update();

            glm::vec2 GetFramebufferSize() const;

            SDL_Window*  GetWindow() { return m_Window; };
            SDL_Surface* GetSurface() { return m_Surface; };
        private:
            SDL_Window*             m_Window;
            SDL_GLContext           m_GLContext;
            SDL_Surface*            m_Surface;
            WindowSpecification     m_Specification;
    };
}

#endif