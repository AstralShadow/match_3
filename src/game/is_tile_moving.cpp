#include "game/move_queue.hpp"


bool game::is_tile_moving(Point pos)
{
    for(auto& collection : {active_moves, failed_moves})
    for(auto pair : collection) {
        auto p1 = pair.first.first;
        auto p2 = pair.first.second;
        if(pos.x == p1.x)
            if(pos.y == p1.y)
                return true;
        if(pos.x == p2.x)
            if(pos.y == p2.y)
                return true;
    }

    return false;
}

