#include "game/tile.hpp"
#include "game/move_queue.hpp"
#include "game/tile_lines.hpp"


bool game::is_tile_in_use(Point pos)
{
    if(is_tile_moving(pos))
        return true;

    if(is_tile_in_line(pos))
        return true;


    return false;
}

