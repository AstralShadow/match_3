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
    SDL_SetRenderDrawBlendMode
        (rnd, SDL_BLENDMODE_BLEND);

    SDL_RenderFillRect(rnd, &line_top);
    SDL_RenderFillRect(rnd, &line_bottom);
    SDL_RenderFillRect(rnd, &line_left);
    SDL_RenderFillRect(rnd, &line_right);

    switch(kb_data.state) {
        case KB_IDLE:
            break;
        case KB_FOCUS:
            render_tile_focus_arrows(output);
            break;
        case KB_FOCUS_DIAGONAL:
            render_tile_focus_diagonals(output);
            break;
    }

    SDL_SetRenderDrawBlendMode
        (rnd, SDL_BLENDMODE_NONE);
}

#include <thread>
#include <chrono>
#include <iostream>

using std::cout;
using std::endl;

void game::
render_tile_focus_arrows(SDL_Rect output)
{
    const int arrow_fraction = 5;
    const int line_width = 2;

    Point size {
        output.w / arrow_fraction,
        output.h / arrow_fraction
    };

    Point center {
        output.x + output.w / 2,
        output.y + output.h / 2
    };

    const int group_size = 4;
    Point vertices[] { Point
        /* Left */
        {output.x - size.x, center.y},
        {output.x - size.x / 2, center.y + size.x / 2},
        {output.x - size.x / 2, center.y - size.x / 2},
        {output.x - size.x, center.y},

        /* Top */
        {center.x, output.y - size.y},
        {center.x + size.x / 2, output.y - size.y / 2},
        {center.x - size.x / 2, output.y - size.y / 2},
        {center.x, output.y - size.y},

        /* Right */ {}, {}, {}, {},
        /* Bottom */ {}, {}, {}, {},
    };

    /* Reflecting left & top to right & bottom */
    for(int i = 0; i < group_size * 2; i++) {
        auto first = vertices;
        auto second = vertices + group_size * 2;
        second[i].x = 2 * center.x - first[i].x;
        second[i].y = 2 * center.y - first[i].y;
    }

    int groups = (sizeof(vertices)
                  / sizeof(vertices[0])) / group_size;
    for(int g = 0; g < groups; g++) {
        auto first = vertices + g * group_size;

        for(int i = 0; i < line_width; i++) {
            SDL_RenderDrawLines(rnd, first, group_size);

            Point mid {0, 0};
            for(int i = 0; i < group_size; i++) {
                mid.x += first[i].x;
                mid.y += first[i].y;
            }
            mid.x /= group_size;
            mid.y /= group_size;

            for(int i = 0; i < group_size; i++) {
                if(first[i].x < mid.x)
                    first[i].x++;
                if(first[i].x > mid.x)
                    first[i].x--;
                if(first[i].y < mid.y)
                    first[i].y++;
                if(first[i].y > mid.y)
                    first[i].y--;
            }
        }
    }
}

void game::
render_tile_focus_diagonals(SDL_Rect output)
{

}

