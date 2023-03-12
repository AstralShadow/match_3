#include "game/render.hpp"
#include "game/board.hpp"
#include "game/move_queue.hpp"


bool game::apply_tile_move_anim(Point pos,
                                SDL_Rect& output)
{
    SDL_Point size {
        board_area.w / board.width,
        board_area.h / board.height
    };

    for(auto& collection : {active_moves, failed_moves})
    for(auto pair : collection) {
        Point p[2] {
            pair.first.first,
            pair.first.second
        };
        auto progress = pair.second;

        int dx = p[1].x - p[0].x;
        int dy = p[1].y - p[0].y;

        for(int i = 0; i < 2; i++)
        if(pos.x == p[i].x && pos.y == p[i].y) {
            auto& p = progress;
            output.x += pow(-1, i) * size.x * dx * p;
            output.y += pow(-1, i) * size.y * dy * p;
            return true;
        }
    }
    return false;
}

