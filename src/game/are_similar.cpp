#include "game/tile.hpp"


bool game::are_similar(Tile* a, Tile* b)
{
    return a->color == b->color;
}

