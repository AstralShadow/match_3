#ifndef INCLUDE_CONFIG_KEYBOARD_CONFIG_HPP
#define INCLUDE_CONFIG_KEYBOARD_CONFIG_HPP

#include "utils/types.hpp"
#include <SDL2/SDL_keyboard.h>
#include <array>

namespace config
{
    using std::array;

    // Array size for player controls
    const int max_kb_players = 2;

    // Determines time before hiding keyboard player
    extern int kb_player_visibility_time;

    // Determines blinks while hiding keyboard player
    const int kb_fade_blinks = 2;

    extern int kb_diagonal_rotation_time;

    const u8 keys_action[] {
        SDL_SCANCODE_SPACE,
        SDL_SCANCODE_RETURN
    };

#ifdef USE_ESDF

    const u8 keys_left[] {
        SDL_SCANCODE_S,
        SDL_SCANCODE_LEFT
    };

    const u8 keys_right[] {
        SDL_SCANCODE_F,
        SDL_SCANCODE_RIGHT
    };

    const u8 keys_up[] {
        SDL_SCANCODE_E,
        SDL_SCANCODE_UP
    };

    const u8 keys_down[] {
        SDL_SCANCODE_D,
        SDL_SCANCODE_DOWN
    };

#else

    const u8 keys_left[] {
        SDL_SCANCODE_A,
        SDL_SCANCODE_LEFT
    };

    const u8 keys_right[] {
        SDL_SCANCODE_D,
        SDL_SCANCODE_RIGHT
    };

    const u8 keys_up[] {
        SDL_SCANCODE_W,
        SDL_SCANCODE_UP
    };

    const u8 keys_down[] {
        SDL_SCANCODE_S,
        SDL_SCANCODE_DOWN
    };

#endif
}

#endif // INCLUDE_CONFIG_KEYBOARD_CONFIG_HPP
