#include "game/board.hpp"

void game::remove_tile(Point pos)
{
    get_tile(pos)->color = 0;
}

