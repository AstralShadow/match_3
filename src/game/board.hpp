#ifndef INCLUDE_GAME_BOARD_HPP
#define INCLUDE_GAME_BOARD_HPP

#include "game/tile.hpp"
#include "utils/point.hpp"


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
    Tile* get_tile(Point);
    Point get_tile_pos(Tile*);

    // Replaces the tile with empty one
    void remove_tile(Point pos);
}

#endif // INCLUDE_GAME_BOARD_HPP
