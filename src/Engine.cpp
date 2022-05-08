#include "Engine.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>
#include <iostream>

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

    float next = SDL_GetTicks();
    float step = 1000.0f / TARGET_FRAMERATE;
    while(_running)
    {
        while(next > SDL_GetTicks());
        next += step;
        int skipped_frames = 0;
        while(next < SDL_GetTicks())
        {
            next += step;
            skipped_frames++;
        }
        if(skipped_frames > 0)
            std::cout << "Skipping " << skipped_frames
                << " frames." << std::endl;

        poll_events();
        tick((1 + skipped_frames) * step);
        render();
    }
}
