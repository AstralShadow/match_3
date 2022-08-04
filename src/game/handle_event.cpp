#include "game/game.hpp"
#include "core/core.hpp"
#include <SDL2/SDL_events.h>


template<>
void game::handle_event(SDL_KeyboardEvent& ev)
{
    if(ev.keysym.sym == SDLK_q)
        core::stop();
}


template<>
void game::handle_event(SDL_MouseButtonEvent&)
{

}

template<>
void game::handle_event(SDL_MouseMotionEvent&)
{

}

template<>
void game::handle_event(SDL_MouseWheelEvent&)
{

}


template<>
void game::handle_event(SDL_DropEvent&)
{

}
