#include "game/game.hpp"
#include "game/board.hpp"
#include "game/move_queue.hpp"

namespace game
{
    queue<move_t> move_queue;
};


void game::init(int, char**, scene_uid)
{
    init_board(8, 8);

}

void game::deinit(scene_uid)
{

}
