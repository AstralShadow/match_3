#include "game/move_queue.hpp"
#include "game/tile.hpp"


bool game::is_tile_in_use(Point pos)
{
    return is_tile_moving(pos);
}

