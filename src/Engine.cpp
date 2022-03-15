#include "Engine.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>

const char* TITLE = "Match 3";
const int WIDTH = 800;
const int HEIGHT = 600;


Engine::Engine()
{
    if(SDL_Init(SDL_INIT_VIDEO))
        throw std::runtime_error(SDL_GetError());

    _window = SDL_CreateWindow(
        TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT,
        0
    );
    if(!_window)
        throw std::runtime_error(SDL_GetError());

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

}
