#include "Board.hpp"
#include <algorithm>

void Board::tick(uint8_t progress)
{
    bool new_tiles = false;

    auto tile = _tiles;
    auto end = _tiles + _w * _h;
    while(tile != end)
    {
        auto* state = get_state(tile);
        uint8_t animation = *state & ANIMATION_MASK;
        uint8_t animation_progress =
            std::min(progress, animation);

        if(animation)
            *state -= animation_progress;


        if(STATE_BREAKING == *state)
            fill(tile);

        if(STATE_FALLING == *state
            || STATE_RETURNING_UP == *state
            || STATE_RETURNING_DOWN == *state
            || STATE_RETURNING_LEFT == *state
            || STATE_RETURNING_RIGHT == *state)
        {
            *state = STATE_NORMAL;
            new_tiles = true;
        }

        if(STATE_SWAPPING_RIGHT == *state)
            swap(tile, tile + 1, true);

        if(STATE_SWAPPING_DOWN == *state)
            swap(tile, tile + _w, true);

        tile++;
    }

    if(new_tiles)
        check_all();
}

