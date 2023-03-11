#include "config/controls.hpp"

bool config::quick_draw = false;
// TODO make diagonals possible when quick_draw = true


#include "config/game.hpp"

bool config::allow_diagonal_moves = true;
bool config::detect_diagonal_lines = !false;
bool config::requeue_waiting_moves = false;
bool config::permit_free_moves = false;
bool config::permit_diagonal_falling = true;
bool config::detect_lines_when_falling = false;
bool config::falling_only_when_board_idle = false;

/* Animations (ms) */
int config::move_duration = 120;
int config::break_duration = 200;
int config::fall_duration = 350;
int config::fall_delay = 500;
float config::fall_delay_factor = 0.15;


