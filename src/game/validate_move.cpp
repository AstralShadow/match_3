#include "game/move_queue.hpp"
#include "config/game.hpp"
#include <cmath>

using std::abs;


void game::validate_move(move_t& move)
{
    auto delta = move.second;
    delta.x -= move.first.x;
    delta.y -= move.first.y;

    if(delta.x > 1)
        move.second.x -= delta.x - 1; 
    if(delta.y > 1)
        move.second.y -= delta.y - 1; 
    if(delta.x < -1)
        move.second.x -= delta.x + 1; 
    if(delta.y < -1)
        move.second.y -= delta.y + 1; 


    delta = move.second;
    delta.x -= move.first.x;
    delta.y -= move.first.y;

    if(!config::allow_diagonal_moves)
        if(delta.x != 0 && delta.y != 0)
            move.second.y = move.first.y;
}
