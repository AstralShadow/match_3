#include "game/render.hpp"
#include "game/keyboard.hpp"
#include "game/tile.hpp"
#include "game/line_animation.hpp"
#include "game/board.hpp"
#include "game/colors.hpp"
#include "core/core.hpp"
#include "utils/pi.hpp"
#include "config/keyboard.hpp"
#include <SDL2/SDL_render.h>
#include <memory>
#include <iostream>
using std::cout;
using std::endl;

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


    if(kb_data.state != KB_IDLE)
        render_tile_focus_arrows(output, kb_data);

    SDL_SetRenderDrawBlendMode
        (rnd, SDL_BLENDMODE_NONE);
}

void game::
render_tile_focus_arrows(SDL_Rect output,
                         KBPlayer const& kb_data)
{
    const int arrow_fraction = 5;

    FPoint size {
        1.0f * output.w / arrow_fraction,
        1.0f * output.h / arrow_fraction
    };

    FPoint center {
        output.x + output.w / 2.0f,
        output.y + output.h / 2.0f
    };

    /* Hard code triangle vertices */
    const int group_size = 4;
    FPoint vertices[] { FPoint
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
    u32 vertices_count = (sizeof(vertices)
                          / sizeof(vertices[0]));

    /* Reflecting left & top to right & bottom */
    for(int i = 0; i < group_size * 2; i++) {
        auto first = vertices;
        auto second = vertices + group_size * 2;
        second[i].x = 2 * center.x - first[i].x;
        second[i].y = 2 * center.y - first[i].y;
    }

    /* Rotate diagonals */
    if(kb_data.state == KB_FOCUS_DIAGONAL) {
        float angle = -pi_f() / 4;
        float scale = sqrt(2);

        int time = config::kb_player_visibility_time
                   - kb_data.visibility_time;
        int rtime = config::kb_diagonal_rotation_time;
        if(time < rtime) {
            angle = angle * time / rtime;
            scale = 1 + (scale - 1) * time / rtime;
        }

        for(u32 i = 0; i < vertices_count; i++) {
            FPoint delta {
                vertices[i].x - center.x,
                vertices[i].y - center.y
            };

            auto _angle = atan2(delta.y, delta.x);
            auto _dist = hypot(delta.y, delta.x);

            _angle += angle;
            _dist *= scale;

            vertices[i] = {
                cos(_angle) * _dist,
                sin(_angle) * _dist
            };
            vertices[i].x += center.x;
            vertices[i].y += center.y;
        }
    }


    int groups = vertices_count / group_size;
    for(int g = 0; g < groups; g++) {
        auto first = vertices + g * group_size;
        Point points[group_size];
        for(int i = 0; i < group_size; i++)
            points[i] = {
                static_cast<int>(first[i].x),
                static_cast<int>(first[i].y)
            };

        SDL_RenderDrawLines(rnd, points, group_size);
    }
}

