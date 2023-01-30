#include "game/game.hpp"
#include "core/core.hpp"
#include <SDL2/SDL_render.h>

static auto& rnd = core::renderer;


void game::render(scene_uid)
{
    SDL_RenderClear(rnd);

    SDL_RenderPresent(rnd);
}
