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

