#include "Engine.hpp"
#include "GameData.hpp"
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

            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                process(ev.button);
                break;
        }
    }
}

void Engine::process(SDL_MouseButtonEvent& ev)
{
    auto const& type = ev.type;
    auto const& UP = SDL_MOUSEBUTTONUP;
    auto const& DOWN = SDL_MOUSEBUTTONDOWN;

    auto const& btn = ev.button;
    auto const& LEFT = SDL_BUTTON_LEFT;
    auto const& RIGHT = SDL_BUTTON_RIGHT;


    if(btn == LEFT && type == DOWN)
    {
        auto* tile = get_tile_at(ev.x, ev.y);
        auto* selected = _data->board.get_selected();
        if(!selected)
            _data->board.select(tile);
        else if(selected != tile)
        {
            _data->board.move(tile);
            _data->board.select(nullptr);
        }
    }

    if(btn == LEFT && type == UP)
    {
        auto* tile = get_tile_at(ev.x, ev.y);
        auto* selected = _data->board.get_selected();
        if(selected != tile)
        {
            _data->board.move(tile);
            _data->board.select(nullptr);
        }
    }
}

