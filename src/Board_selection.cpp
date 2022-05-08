#include "Board.hpp"
#include <iterator>


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

void Board::move(tile_t* target)
{
    if(!_selected || !target)
        return;
    if(STATE_NORMAL != *get_state(_selected))
        return;
    
    int pos1 = std::distance(_tiles, _selected);
    int pos2 = std::distance(_tiles, target);
    int x1 = pos1 % _w, y1 = pos1 / _w;
    int x2 = pos2 % _w, y2 = pos2 / _w;
    int dx = x2 - x1,   dy = y2 - y1;


    const auto animated = ANIMATION_MASK;
    const auto LEFT = STATE_SWAPPING_LEFT + animated;
    const auto RIGHT = STATE_SWAPPING_RIGHT + animated;
    const auto UP = STATE_SWAPPING_UP + animated;
    const auto DOWN = STATE_SWAPPING_DOWN + animated;

    using std::abs;
    if(abs(dx) > abs(dy))
    {
        if(dx > 0 && x1 < _w - 1)
        {
            if(STATE_NORMAL != *get_state(_selected + 1))
                return;
            *get_state(_selected) = RIGHT;
            *get_state(_selected + 1) = LEFT;
        }
        if(dx < 0 && x1 > 0)
        {
            if(STATE_NORMAL != *get_state(_selected - 1))
                return;
            *get_state(_selected) = LEFT;
            *get_state(_selected - 1) = RIGHT;
        }
    }
    else if(abs(dx) < abs(dy))
    {
        if(dy > 0 && y1 < _h - 1)
        {
            if(STATE_NORMAL != *get_state(_selected + _w))
                return;
            *get_state(_selected) = DOWN;
            *get_state(_selected + _w) = UP;
        }
        if(dy < 0 && y1 > 0)
        {
            if(STATE_NORMAL != *get_state(_selected - _w))
                return;
            *get_state(_selected) = UP;
            *get_state(_selected - _w) = DOWN;
        }
    }
}

