#include "Board.hpp"
#include <iterator>


void Board::move_up()
{
    move_to_tile_offset(-_w);
}

void Board::move_left()
{
    move_to_tile_offset(-1);
}

void Board::move_down()
{
    move_to_tile_offset(_w);
}

void Board::move_right()
{
    move_to_tile_offset(1);
}

void Board::move_to_tile_offset(int offset)
{
    if(!_focused) _focused = _tiles;

    int pos_focused = std::distance(_tiles, _focused);
    int new_pos = pos_focused + offset;
    if(new_pos < 0 || new_pos >= _w * _h)
        return;

    _focused = _tiles + new_pos;

    if(_selected)
    {
        move(_focused);
        _selected = nullptr;
    }
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

