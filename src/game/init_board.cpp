#include "game/board.hpp"

#include <iostream>
using std::cout;
using std::endl;

namespace game {
    Board board;
}


void game::init_board(int width, int height)
{
    u32 size = width * height;

    board.width = width;
    board.height = height;

    board.data = new Tile[size]();


    int ram_usage = size * sizeof board.data[0];
    cout << "Board size: "
         << width << "x" << height << endl;
    cout << "Board RAM: " << ram_usage << " B" << endl;


    for(u32 i = 0; i < size; i++)
        *(board.data + i) = create_tile();
}

