#include "game/render.hpp"
#include "game/keyboard.hpp"
#include "game/tile.hpp"
#include "game/line_animation.hpp"
#include "game/board.hpp"
#include "game/colors.hpp"
#include "core/core.hpp"
#include <SDL2/SDL_render.h>

using game::Tile;


static auto& rnd = core::renderer;

namespace game
{
    static void set_color(Tile*);
}


void game::render_tile(Tile* tile, SDL_Rect output)
{
    if(is_tile_empty(tile))
        return;

    set_color(tile);

    SDL_RenderFillRect(rnd, &output);
}


void game::set_color(Tile* tile)
{
    auto color = game::colors[tile->color];

    Point pos = get_tile_pos(tile);
    float broken = get_line_animation_progress(pos);
    color.r *= 1 - broken;
    color.g *= 1 - broken;
    color.b *= 1 - broken;

    SDL_SetRenderDrawColor(rnd,
        color.r, color.g, color.b, 255);
}

