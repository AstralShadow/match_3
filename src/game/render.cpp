#include "game/game.hpp"
#include "game/render.hpp"
#include "core/core.hpp"
#include <SDL2/SDL_render.h>

static auto& rnd = core::renderer;

namespace game
{
    SDL_Rect board_area {
        200, // 200 + (600 - 512) / 2,
        0, //(600 - 512) / 2,
        600, 600 //512, 512
    };
}


void game::render(scene_uid)
{
    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderClear(rnd);

    render_board();

    SDL_RenderPresent(rnd);
}
