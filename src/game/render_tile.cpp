#include "game/render.hpp"
#include "game/keyboard.hpp"
#include "game/tile.hpp"
#include "game/tile_lines.hpp"
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
    float break_progress = get_tile_line_progress(pos);
    color.r *= 1 - break_progress;
    color.g *= 1 - break_progress;
    color.b *= 1 - break_progress;

    SDL_SetRenderDrawColor(rnd,
        color.r, color.g, color.b, 255);
}


void game::
render_tile_focus_frame(SDL_Rect output,
                        KBPlayer const& kb_data,
                        u8 opacity)
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


    SDL_SetRenderDrawColor(rnd, 0, 0, 0, opacity);
    SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_BLEND);

    SDL_RenderFillRect(rnd, &line_top);
    SDL_RenderFillRect(rnd, &line_bottom);
    SDL_RenderFillRect(rnd, &line_left);
    SDL_RenderFillRect(rnd, &line_right);

    switch(kb_data.state) {
        
    }

    SDL_SetRenderDrawBlendMode(rnd, SDL_BLENDMODE_NONE);
}
