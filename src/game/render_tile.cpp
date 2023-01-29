#include "game/render.hpp"
#include "game/tile.hpp"
#include "game/colors.hpp"
#include "core/core.hpp"
#include <SDL2/SDL_render.h>

using game::Tile;

static auto& rnd = core::renderer;
static void set_color(Tile*);


void game::render_tile(Tile* tile, SDL_Rect output)
{
    set_color(tile);

    SDL_RenderFillRect(rnd, &output);
}


void set_color(Tile* tile)
{
    auto color = game::colors[tile->color];
    SDL_SetRenderDrawColor(rnd,
        color.r, color.g, color.b, 255);
}

void game::render_tile_focus_frame(SDL_Rect output)
{
    int weight = 3;

    SDL_Rect line_top {
        output.x + weight,
        output.y + weight,
        output.w - weight * 2,
        weight
    };

    SDL_Rect line_bottom {
        output.x + weight,
        output.y + output.h - weight * 2,
        output.w - weight * 2,
        weight
    };

    SDL_Rect line_left {
        output.x + weight,
        output.y + weight,
        weight,
        output.h - weight * 2,
    };

    SDL_Rect line_right {
        output.x + output.w - weight * 2,
        output.y + weight,
        weight,
        output.h - weight * 2,
    };


    SDL_SetRenderDrawColor(rnd, 0, 0, 0, 255);
    SDL_RenderFillRect(rnd, &line_top);
    SDL_RenderFillRect(rnd, &line_bottom);
    SDL_RenderFillRect(rnd, &line_left);
    SDL_RenderFillRect(rnd, &line_right);
}
