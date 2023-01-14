#include "game/game.hpp"
#include "game/board.hpp"


void game::init(int, char**, scene_uid)
{
    init_board(8, 8);

}

void game::deinit(scene_uid)
{

}
