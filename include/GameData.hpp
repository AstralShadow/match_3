#ifndef INCLUDE_GAMEDATA_HPP
#define INCLUDE_GAMEDATA_HPP

#include <utility>
#include "Board.hpp"

struct GameData
{
    GameData(Board&& __board) :
        board(std::move(__board)) {}

    Board board;
};

#endif // INCLUDE_GAMEDATA_HPP
