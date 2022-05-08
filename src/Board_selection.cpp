#include "Board.hpp"
#include <iterator>
#include <iostream>


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
    
    int pos1 = std::distance(_tiles, _selected);
    int pos2 = std::distance(_tiles, target);
    int x1 = pos1 % _w, y1 = pos1 / _w;
    int x2 = pos2 % _w, y2 = pos2 / _w;
    int dx = x2 - x1,   dy = y2 - y1;

    using std::abs;
    if(abs(dx) > abs(dy))
    {
        if(dx > 0 && x1 < _w - 1)
            swap(_selected + 1);
        if(dx < 0 && x1 > 0)
            swap(_selected - 1);
    }
    else if(abs(dx) < abs(dy))
    {
        if(dy > 0 && y1 < _h - 1)
            swap(_selected + _w);
        if(dy < 0 && y1 > 0)
            swap(_selected - _w);
    }
}

void Board::swap(tile_t* other)
{
    if(!other)
        std::cout << "Swapping nullptr." << std::endl;

    const auto state1 = *get_state(_selected);
    const auto state2 = *get_state(other);
    if(STATE_NORMAL == state1 && STATE_NORMAL == state2)
    {
        std::swap(*other, *_selected);
        auto pos1 = std::distance(_tiles, _selected);
        auto pos2 = std::distance(_tiles, other);
        auto x1 = pos1 % _w;
        auto y1 = pos1 / _w;
        auto x2 = pos2 % _w;
        auto y2 = pos2 / _w;

        bool match = false;
        for(int i = 2; i >= 0; i--)
        {
            match = check((*this)(x1 - i, y1)) || match;
            match = check((*this)(x1, y1 - i)) || match;
            match = check((*this)(x2 - i, y2)) || match;
            match = check((*this)(x2, y2 - i)) || match;
        }
        if(!match)
        {
            std::swap(*other, *_selected);
        }
    }
}

