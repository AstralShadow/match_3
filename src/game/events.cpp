#include "game/game.hpp"
#include "core/core.hpp"
#include <SDL2/SDL_events.h>


void game::keydown(SDL_KeyboardEvent& ev, scene_uid)
{
    if(ev.keysym.sym == SDLK_q)
        core::stop();
}
