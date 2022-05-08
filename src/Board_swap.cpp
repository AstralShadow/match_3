#include "Board.hpp"
#include <iterator>
#include <iostream>


void Board::swap(tile_t* first, tile_t* second,
                 bool animated)
{
    auto state1 = *get_state(first) & STATE_MASK;
    auto state2 = *get_state(second) & STATE_MASK;

    auto pos1 = std::distance(_tiles, first);
    auto pos2 = std::distance(_tiles, second);
    auto x1 = pos1 % _w; auto y1 = pos1 / _w;
    auto x2 = pos2 % _w; auto y2 = pos2 / _w;

    *get_state(first) = STATE_NORMAL;
    *get_state(second) = STATE_NORMAL;

    std::swap(*first, *second);

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
        std::swap(*first, *second);

        if(!animated) return;

        auto reverse = STATE_SWAPPING_TO_RETURNING;
        auto animated = ANIMATION_MASK;

        *get_state(first)  = state1 + reverse + animated;
        *get_state(second) = state2 + reverse + animated;
    }
}

