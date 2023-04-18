#include "game/game.hpp"
#include "game/render.hpp"
#include "core/core.hpp"
#include "config/graphics.hpp"
#include <SDL2/SDL_render.h>

static auto& rnd = core::renderer;


void game::render(scene_uid)
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    render_resize();
    render_board();

    if(config::display_version_tag)
        render_version_tag();

    SDL_RenderPresent(rnd);
}

