#include "game/game.hpp"
#include <SDL2/SDL_events.h>


template<>
void game::handle_event(SDL_KeyboardEvent&)
{

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
