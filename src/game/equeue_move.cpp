#include "game/move_queue.hpp"


void game::equeue_move(move_t move)
{
    input_queue.push(move);
}

