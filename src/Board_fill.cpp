#include "Board.hpp"
#include <iterator>
#include <random>

using std::uniform_int_distribution;
static std::random_device rd;
static std::mt19937 generator(rd());
static uniform_int_distribution<int> type_dist(1, 6);
static uniform_int_distribution<int> bonus_dist(0, 37);
static int bonus_chance = 3;


void Board::fill(tile_t* tile)
{
    auto* state = get_state(tile);
    int pos = std::distance(_tiles, tile);
    int y = pos / _w;

    if(y == 0)
    {
        *tile = type_dist(generator);
        if(bonus_dist(generator) < bonus_chance)
            *tile += TILE_BONUS;

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
