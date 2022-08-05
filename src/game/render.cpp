#include "game/game.hpp"
#include "core/core.hpp"
#include <SDL2/SDL_render.h>

using core::renderer;


void game::render(scene_uid)
{
    SDL_RenderClear(core::renderer);

    SDL_RenderPresent(core::renderer);
}
