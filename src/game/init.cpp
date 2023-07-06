#include "game/game.hpp"
#include "game/board.hpp"
#include "game/move_queue.hpp"
#include "game/falling_tiles.hpp"

namespace game
{
    queue<move_t> input_queue;
    map<move_t, float> active_moves;
    map<move_t, float> failed_moves;
    vector<FallingTiles> falling_tiles;
};


void game::init(int, char**, scene_uid)
{
    init_board(10, 8);

}

void game::deinit(scene_uid)
{

}
