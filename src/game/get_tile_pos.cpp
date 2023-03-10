#include "game/board.hpp"

using game::Tile;


Point game::get_tile_pos(Tile* t)
{
    if(t == nullptr)
        return {-1, -1};

    int size = board.width * board.height;

    int distance = t - board.data;
    if(distance < 0 || distance > size - 1)
        return {-1, -1};

    return {
        distance % board.width,
        distance / board.width
    };
}

