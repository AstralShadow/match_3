#ifndef INCLUDE_CONFIG_GAME_HPP
#define INCLUDE_CONFIG_GAME_HPP

namespace config
{
    /* Mechanics */

    // Wether to allow diagonal tile swaps
    extern bool allow_diagonal_moves; // TODO use

    // Wether to detect lines on diagonals
    extern bool detect_diagonal_lines;

    // Wether to requeue or drop moves on busy tiles
    extern bool requeue_waiting_moves;

    // Free moves are moves that don't form a line
    extern bool permit_free_moves;


    /* Animations*/

    // Move animation duration in ms
    extern int move_duration;

    // Line break animation duration in ms
    extern int break_duration;
}

#endif // INCLUDE_CONFIG_GAME_HPP
