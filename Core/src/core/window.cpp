#include "window.h"

#include <iostream>
#include <glad/glad.h>

namespace Engine {

	Window::Window(const WindowSpecification& specification)
		: m_Specification(specification)
	{
	}

	Window::~Window()
	{
		DestroyWindow();
		DestroySurface();
	}

	void Window::CreateWindow()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			std::cout << "Failed to initialize the window\n";
			return;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		m_Window = SDL_CreateWindow(m_Specification.Title.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			m_Specification.Width,
			m_Specification.Height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		if (m_Window == nullptr)
		{
			std::cout << "Failed to create the window\n";
			return;
		}

		if (!m_Window)
		{
			SDL_Log("Window pointer is null!");
			return;
		}

		m_GLContext = SDL_GL_CreateContext(m_Window);

		gladLoadGLLoader(SDL_GL_GetProcAddress);

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    		std::cout << "Failed to initialize GLAD" << std::endl;
		}

		// CreateSurface();
	}

	void Window::DestroyWindow()
	{
		SDL_DestroyWindow(m_Window);
	}

	void Window::DestroySurface()
	{
		SDL_FreeSurface(m_Surface);
	}

	void Window::Update()
	{
		SDL_GL_SwapWindow(m_Window);
	}

	glm::vec2 Window::GetFramebufferSize() const
	{
		int width, height;
		SDL_GetWindowSize(m_Window, &width, &height);
		return { width, height };
	}

	void Window::CreateSurface()
	{
		m_Surface = SDL_GetWindowSurface(m_Window);

		if (m_Surface == nullptr)
			std::cout << "Failed to get the surface from the window\n";
		return;
	}
}