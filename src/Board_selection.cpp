#include "Board.hpp"
#include <iterator>


void Board::focus(tile_t* tile)
{
    _focused = tile;
}

void Board::select(tile_t* tile)
{
    if(nullptr == tile)
    {
        _selected = nullptr;
        return;
    }

    const auto state = *get_state(tile);
    if(STATE_NORMAL == state)
        _selected = tile;
}
