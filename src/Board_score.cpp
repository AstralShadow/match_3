#include "Board.hpp"
#include <cmath>
#include <iostream>

#define PRINT_SCORE true
using std::cout;
using std::endl;



void Board::assign_score(tile_t* tile, int combo)
{
    auto type = *tile & TILE_TYPE_MASK;
    _color_score[type] += std::pow(combo, 1.27);

    if(*tile & TILE_BONUS)
        _color_score[type] += std::pow(combo, 2.54);


    if(_last_type == type)
    {
        _total_color_combo++;
        _color_score[type] += _total_color_combo / combo;
    }
    else _total_color_combo = 0;

    _last_type = type;

#if __EMSCRIPTEN__
    #undef PRINT_SCORE
    #define PRINT_SCORE false
#endif

#if PRINT_SCORE
    for(int i = 0; i < TILE_TYPE_MASK; i++)
    {
        if(_color_score[i])
            cout << "Score[" << i << "] = "
                << _color_score[i] << endl;
    }
    cout << endl;
#endif

}
