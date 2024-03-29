#include "game/board.hpp"

#include <iostream>
using std::cout;
using std::endl;

namespace game {
    Board board;
}


void game::init_board(u32 width, u32 height)
{
    u32 size = width * height;

    board.width = width;
    board.height = height;

    board.data = new Tile[size]();


    int ram_usage = size * sizeof board.data[0];
    cout << "Board size: "
         << width << "x" << height << endl;
    cout << "Board RAM: " << ram_usage << " B" << endl;

}

