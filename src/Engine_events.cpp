#include "Engine.hpp"
#include <SDL2/SDL.h>


void Engine::poll_events()
{
    SDL_Event ev;
    while(SDL_PollEvent(&ev))
    {
        switch(ev.type)
        {
            case SDL_QUIT:
                _running = false;
                break;
        }
    }
}
