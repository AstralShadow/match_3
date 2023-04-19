#include "game/game.hpp"
#include "game/move_queue.hpp"
#include "game/line_animation.hpp"
#include "game/falling_tiles.hpp"
#include "game/keyboard.hpp"


void game::tick(u32 time, scene_uid)
{
    process_moves(time);
    process_line_animations(time);
    process_falling_tiles(time);
    fade_unused_keyboard_players(time);
}
