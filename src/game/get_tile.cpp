#include "game/board.hpp"

using game::Tile;


Tile* game::get_tile(int x, int y)
{
    int size = board.width * board.height;

    int pos = x + y * board.width;
    if(pos < 0)
        return nullptr;

    if(pos < size)
        return board.data + pos;

    return nullptr;
}

