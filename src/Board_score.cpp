#include "Board.hpp"
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

void Board::assign_score(tile_t* tile, int combo)
{
    auto type = *tile & TILE_TYPE_MASK;
    _color_score[type] += std::pow(combo, 1.27);

    if(*tile & TILE_BONUS)
        _color_score[type] += std::pow(combo, 2.54);

    for(int i = 0; i < TILE_TYPE_MASK; i++)
    {
        cout << "Score[" << i << "] = "
            << _color_score[i] << endl;
    }
    cout << endl;
}
