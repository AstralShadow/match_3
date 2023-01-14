#ifndef INCLUDE_BOARD_HPP
#define INCLUDE_BOARD_HPP

#include "game/tile.hpp"


namespace game
{

    struct Board
    {
        int width;
        int height;
        Tile* data = nullptr;
    };

    extern Board board;


    void init_board(int width, int height);

    Tile* get_tile(int x, int y);
}

#endif // INCLUDE_BOARD_HPP
