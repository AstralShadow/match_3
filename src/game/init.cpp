#include "game/game.hpp"
#include "game/board.hpp"


void game::init(int, char**, scene_uid)
{
    init_board(32, 32);

}

void game::deinit(scene_uid)
{

}
