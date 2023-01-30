#include "game/game.hpp"
#include "core/core.hpp"
#include <SDL2/SDL_events.h>


void game::keydown(SDL_KeyboardEvent& ev, scene_uid)
{
    auto const& scancode = ev.keysym.scancode;
    if(scancode == SDL_SCANCODE_Q)
        core::stop();
}
