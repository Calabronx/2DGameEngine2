#include "input.h"
#include <iostream> // solo para debug

namespace
{
    const Uint8*    g_KeyboardState = nullptr;
    Uint32          g_MouseState = 0;
    glm::vec2       g_CursorState(0,0);

    bool            g_QuitRequested = false;
}

void Input::Update()
{
    SDL_Event event;

    g_QuitRequested = false;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            g_QuitRequested = true;
        }

        if (event.type == SDL_MOUSEMOTION)
        {
            int x, y;
            SDL_GetMouseState(&x, &y);
            g_CursorState.x = x;
            g_CursorState.y = y;
            // std::cout << "mouse x: " << x << " mouse y: " << y << std::endl;
        }
    }

    g_KeyboardState = SDL_GetKeyboardState(nullptr);
    g_MouseState = SDL_GetMouseState(nullptr, nullptr);
}

bool Input::IsKeyPressed(SDL_Scancode key)
{
    return g_KeyboardState[key];
}

bool Input::IsMousePressed()
{
    return g_MouseState;
}

glm::vec2 Input::GetCursorPosition()
{
    return g_CursorState;
}

bool Input::QuitRequested()
{
    return g_QuitRequested;
}
