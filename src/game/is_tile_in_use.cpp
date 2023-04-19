#include "game/tile.hpp"
#include "game/board.hpp"
#include "game/move_queue.hpp"
#include "game/line_animation.hpp"
#include "game/falling_tiles.hpp"


bool game::is_tile_in_use(Point pos)
{
    if(is_tile_moving(pos))
        return true;

    if(is_tile_in_line(pos))
        return true;

    if(is_tile_empty(pos))
        return true;

    if(is_tile_falling(pos))
        return true;

    return false;
}

