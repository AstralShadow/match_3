#include "game/board.hpp"


bool game::is_tile_empty(Point pos)
{
    Tile* tile = get_tile(pos);
    return is_tile_empty(tile);
}

bool game::is_tile_empty(Tile* tile)
{
    return !tile || tile->color == 0;
}

