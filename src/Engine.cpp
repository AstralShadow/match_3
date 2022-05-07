#include "Engine.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>

Engine::Engine()
{
    if(SDL_Init(SDL_INIT_VIDEO))
        throw std::runtime_error(SDL_GetError());

    create_window();
    create_renderer();
    init_game_data();
}

void Engine::create_window()
{
    _window = SDL_CreateWindow(
        TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT,
        0
    );
    if(!_window)
        throw std::runtime_error(SDL_GetError());
}

void Engine::create_renderer()
{
    _renderer = SDL_CreateRenderer(_window, -1, 0);

    if(!_renderer)
        throw std::runtime_error(SDL_GetError());
}


Engine::~Engine()
{
    if(!_renderer)
        SDL_DestroyRenderer(_renderer);
    if(!_window)
        SDL_DestroyWindow(_window);

    SDL_Quit();
}


void Engine::run()
{
    _running = true;

    int start = SDL_GetTicks();
    while(_running)
    {
        SDL_Delay(10);
        
        int end = SDL_GetTicks();

        poll_events();
        tick(end - start);
        render();

        start = end;
    }
}
