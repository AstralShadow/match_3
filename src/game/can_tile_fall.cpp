#include "game/falling_tiles.hpp"
#include "game/board.hpp"
#include "config/game.hpp"


/*
bool game::can_tile_fall(Point pos)
{
    if(is_tile_in_use(pos))
        return false;

    if(pos.y == board.height - 1)
        return false;

    vector<Point> footholds {Point{pos.x, pos.y + 1}};

    if(config::permit_diagonal_falling) {
        footholds.push_back({pos.x + 1, pos.y + 1});
        footholds.push_back({pos.x - 1, pos.y + 1});
    }

    for(auto foothold : footholds) {
        if(foothold.y >= board.height - 1)
            continue;

        if(is_tile_empty(foothold))
            return true;

        if(can_tile_fall(foothold))
            return true;
    }

    return false;
}

*/
