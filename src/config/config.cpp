#include "config/controls.hpp"

bool config::quick_draw = false;
// TODO make diagonals possible when quick_draw = true
// maybe just use different mouse key for quick_draw


#include "config/game.hpp"

bool config::allow_diagonal_moves = true;
bool config::detect_diagonal_lines = !false;
bool config::requeue_waiting_moves = false;
bool config::permit_free_moves = false;
bool config::permit_diagonal_falling = true;
bool config::detect_lines_when_falling = true;
bool config::falling_only_when_board_idle = false;

/* Animations (ms) */
int config::move_duration = 120;
int config::break_duration = 200;
int config::fall_duration = 250;
int config::fall_delay = 500;
float config::fall_delay_factor = 0.15;

bool config::slower_massive_falls = true;
bool config::slower_massive_falls_based_on_lines = false;
float config::slowness_per_falling_tile = 0.003;


#include "config/keyboard.hpp"

/* Animations (ms) */
int config::kb_player_visibility_time = 15000;
int config::kb_diagonal_rotation_time = 150;


#include "config/graphics.hpp"

bool config::display_version_tag = true;


#include "config/skills.hpp"

u32 config::beam_break_duration = 350;
u32 config::beam_motion_delay = 50;

