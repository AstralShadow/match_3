#include "Board.hpp"
#include <iterator>


bool Board::check(tile_t* tile)
{
    if(tile == nullptr) return false;
    auto breaking = STATE_BREAKING + ANIMATION_MASK;

    auto state = get_state(tile);
    if(STATE_NORMAL != *state && breaking != *state)
        return false;

    int pos = std::distance(_tiles, tile);
    int x = pos % _w;
    int y = pos / _w;

    if(x < _w - 2)
    {
        int same = 0;
        auto* other = tile;
        tile_t* row_end = _tiles + (y + 1) * _w;
        while(other < row_end)
        {
            const auto type_m = TILE_TYPE_MASK;
            auto state2 = *get_state(other);
            if((*other & type_m) != (*tile & type_m) ||
                (STATE_NORMAL != state2
                    && breaking != state2))
            {
                break;
            }
            same++;
            other++;
        }

        if(same > 2) 
        for(int i = 0; i < same; i++)
        {
            assign_score(tile + i, same);
            *get_state(tile + i) = breaking;
        }
    }

    if(y < _h - 2)
    {
        int same = 1;
        auto other = tile + _w;
        tile_t* col_end = _tiles + _h * _w + x;
        while(other < col_end)
        {
            const auto type_m = TILE_TYPE_MASK;
            auto state2 = *get_state(other);
            if((*other & type_m) != (*tile & type_m) ||
                (STATE_NORMAL != state2
                    && breaking != state2))
            {
                break;
            }
            same++;
            other += _w;
        }

        if(same > 2)
        for(int i = 0; i < same; i++)
        {
            assign_score(tile + i * _w, same);
            *get_state(tile + i * _w) = breaking;
        }
    }

    return STATE_NORMAL != *state;
}

bool Board::check_all()
{
    bool result = false;
    for(size_t i = 0; i < size(); i++)
        result = check(_tiles + i) || result;
    return result;
}
