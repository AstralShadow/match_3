#ifndef INCLUDE_GAME_KEYBOARD_HPP
#define INCLUDE_GAME_KEYBOARD_HPP

#include "config/keyboard.hpp"
#include "utils/point.hpp"


namespace game
{
    enum KBState {
        KB_IDLE,
        KB_FOCUS,
        KB_FOCUS_DIAGONAL,
    };

    struct KBPlayer 
    {
        Point pos {0, 0};
        KBState state = KB_IDLE;

        int visibility_time = 0;
    };

    extern KBPlayer kb_players[config::max_kb_players];

    void fade_unused_keyboard_players(int ms);
}

#endif // INCLUDE_GAME_KEYBOARD_HPP
