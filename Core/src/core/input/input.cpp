#include "input.h"

namespace
{
    const Uint8* g_KeyboardState = nullptr;

    bool g_QuitRequested = false;
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
    }

    g_KeyboardState = SDL_GetKeyboardState(nullptr);
}

bool Input::IsKeyPressed(SDL_Scancode key)
{
    return g_KeyboardState[key];
}

bool Input::QuitRequested()
{
    return g_QuitRequested;
}
