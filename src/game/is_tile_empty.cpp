#include "game/board.hpp"


bool game::is_tile_empty(Point pos)
{
    Tile* tile = get_tile(pos);
    return !tile || tile->color == 0;
}
