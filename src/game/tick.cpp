#include "game/game.hpp"
#include "game/move_queue.hpp"


void game::tick(u32 time, scene_uid)
{
    process_moves(time);
}
