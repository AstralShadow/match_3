#include "game/board.hpp"

using game::Tile;


Tile* game::get_tile(Point p)
{
    return get_tile(p.x, p.y);
}

Tile* game::get_tile(int x, int y)
{
    if(x < 0 || x >= board.width)
        return nullptr;
    if(y < 0 || y >= board.height)
        return nullptr;

    int pos = x + y * board.width;
    return board.data + pos;
}

