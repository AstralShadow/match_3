#include "game/line_animation.hpp"
#include "game/board.hpp"
#include <iostream>

using std::cout;
using std::endl;


void game::finish_line_animation(LineAnimationData* data)
{
    // TODO scoring

    Tile* tile = get_tile(data->line[0]);
    cout << "C: " << (i32) tile->color << endl;

    for(Point pos : data->line)
        remove_tile(pos);
}

