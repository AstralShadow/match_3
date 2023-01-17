#include "game/move_queue.hpp"


void game::validate_move(move_t& move)
{
    auto base = move.second;
    base.x -= move.first.x;
    base.y -= move.first.y;

    if(base.x > 1)
        move.second.x -= base.x - 1; 
    if(base.y > 1)
        move.second.y -= base.y - 1; 
    if(base.x < -1)
        move.second.x -= base.x + 1; 
    if(base.y < -1)
        move.second.y -= base.y + 1; 
}
