#include "game/game.hpp"
#include "game/move_queue.hpp"
#include "game/tile_lines.hpp"
#include "game/falling_tiles.hpp"


void game::tick(u32 time, scene_uid)
{
    process_moves(time);
    process_lines(time);
    process_falling_tiles(time);
}
