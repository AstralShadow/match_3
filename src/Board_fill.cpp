#include "Board.hpp"
#include <iterator>
#include <random>

using std::uniform_int_distribution;
static std::random_device rd;
static std::mt19937 generator(rd());
static uniform_int_distribution<int> dist(1, 6);


void Board::fill(tile_t* tile)
{
    auto* state = get_state(tile);
    int pos = std::distance(_tiles, tile);
    int y = pos / _w;

    if(y == 0)
    {
        *tile = dist(generator);
        *state = STATE_FALLING + ANIMATION_MASK;
        return;
    }

    auto* top = tile - _w;
    auto* top_state = get_state(top);
    if(STATE_NORMAL == *top_state)
    {
        *tile = *top;
        *top_state = STATE_BREAKING;
        *state = STATE_FALLING + ANIMATION_MASK;
    }
}
