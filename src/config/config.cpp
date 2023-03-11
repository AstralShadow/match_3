#include "config/controls.hpp"

bool config::quick_draw = true;


#include "config/game.hpp"

bool config::allow_diagonal_moves = true;
bool config::detect_diagonal_lines = !false;
bool config::requeue_waiting_moves = false;
bool config::permit_free_moves = false;

int config::move_duration = 120; // ms
int config::break_duration = 120; // ms


