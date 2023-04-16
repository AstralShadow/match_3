#ifndef INCLUDE_CONFIG_GAME_HPP
#define INCLUDE_CONFIG_GAME_HPP

namespace config
{
    /* Mechanics */

    // Wether to allow diagonal tile swaps
    extern bool allow_diagonal_moves;

    // Wether to detect lines on diagonals
    extern bool detect_diagonal_lines;

    // Wether to requeue or drop moves on busy tiles
    extern bool requeue_waiting_moves;

    // Free moves are moves that don't form a line
    extern bool permit_free_moves;

    // Wether to permit diagonal tile falling
    extern bool permit_diagonal_falling;

    // Wether to detect lines formed while falling
    extern bool detect_lines_when_falling;

    // Wether the falling waits for line destructions
    extern bool falling_only_when_board_idle;


    /* Animations (ms) */

    // Move animation duration
    extern int move_duration;

    // Line break animation duration
    extern int break_duration;

    // Tile falling animation duration for 1 tile height
    extern int fall_duration;

    // Delay before activating tile falling
    extern int fall_delay;

    // What part of the fall duration a tile waits
    //  before activating it's own fall animation
    extern float fall_delay_factor;


    // Make falling slower because it's hard to follow
    //  when too much stuff falls
    extern bool slower_massive_falls; // TODO implement
    // TODO slow down diagonal falling

    // Calculate for lines instead of tiles.
    // Should feel more natural as single 3-tile match
    //  speed shouldn't depend on vertical position.
    extern bool slower_massive_falls_based_on_lines;

    // How much should all falling tiles slow down
    //  per falling tile
    extern float slowness_per_falling_tile;

}

#endif // INCLUDE_CONFIG_GAME_HPP
