#include "game/render.hpp"
#include "game/board.hpp"
#include "game/move_queue.hpp"


void game::render_board()
{
    SDL_Rect output {
        board_area.x,
        board_area.y,
        board_area.w / board.width,
        board_area.h / board.height
    };

    for(int y = 0; y < board.height; y++)
    for(int x = 0; x < board.width; x++) {
        auto tile = get_tile(x, y);

        output.x = board_area.x + output.w * x;
        output.y = board_area.y + output.h * y;

        bool modified_position =
            apply_tile_animation(x, y, output);

        render_tile(tile, output);

        if(!modified_position)
        if(x == keyboard_focus.x)
        if(y == keyboard_focus.y)
            render_tile_focus_frame(output);
    }
}

bool game::apply_tile_animation(int x, int y, SDL_Rect& output)
{
    SDL_Point size = {
        board_area.w / board.width,
        board_area.h / board.height
    };

    for(auto& collection : {active_moves, failed_moves})
    for(auto pair : collection)
    {
        Point p[2] {
            pair.first.first,
            pair.first.second
        };
        auto progress = pair.second;

        int dx = p[1].x - p[0].x;
        int dy = p[1].y - p[0].y;

        for(int i = 0; i < 2; i++) {
            if(x == p[i].x && y == p[i].y) {
                output.x += pow(-1, i) * size.x * progress * dx;
                output.y += pow(-1, i) * size.y * progress * dy;
                return true;
            }
        }
    }
    return false;
}

