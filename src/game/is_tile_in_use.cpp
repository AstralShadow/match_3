#include "game/tile.hpp"
#include "game/board.hpp"
#include "game/move_queue.hpp"
#include "game/line_animation.hpp"
#include "game/falling_tiles.hpp"
#include "game/skill.hpp"


bool game::is_tile_in_use(Point pos, u32 ignore)
{
    if(!(ignore && CHK_IGNORE_MOVING))
        if(is_tile_moving(pos))
            return true;

    if(!(ignore && CHK_IGNORE_IN_LINE))
        if(is_tile_in_line(pos))
            return true;

    if(!(ignore && CHK_IGNORE_EMPTY))
        if(is_tile_empty(pos))
            return true;

    if(!(ignore && CHK_IGNORE_FALLING))
        if(is_tile_falling(pos))
            return true;


    return false;
}

