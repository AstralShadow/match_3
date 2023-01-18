#include "game/game.hpp"
#include "core/core.hpp"
#include "utils/point.hpp"
#include "game/render.hpp"
#include "game/board.hpp"
#include "game/move_queue.hpp"
#include "config/controls.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>

using std::endl;
using std::cout;
using ButtonEv = SDL_MouseButtonEvent;
using MotionEv = SDL_MouseMotionEvent;

static Point mouse_focus {0, 0};
static bool pending_move = false;
static bool const print_log = true;

Point game::get_board_pos(int x, int y)
{
    return {
        (x - board_area.x) * board.width / board_area.w,
        (y - board_area.y) * board.height / board_area.h
    };
}


void game::mousedown(ButtonEv& ev, scene_uid)
{
    Point pos = get_board_pos(ev.x, ev.y);
    mouse_focus = pos;
    pending_move = true;
    if(print_log)
        cout << "Pending move from "
             << pos.x << "x" << pos.y << endl;
}

void game::mouseup(ButtonEv& ev, scene_uid)
{
    if(!pending_move)
        return;
    Point pos = get_board_pos(ev.x, ev.y);

    move_t move {mouse_focus, pos};
    validate_move(move);
    pos = move.second;
    input_queue.push(move);
    pending_move = false;
    if(print_log)
        cout << "Move to " << pos.x
             << "x" << pos.y << endl;
}

void game::mouse_motion(MotionEv& ev,
                        scene_uid)
{
    if(!pending_move || !config::quick_draw)
        return;
    Point pos = get_board_pos(ev.x, ev.y);
    if(pos.x != mouse_focus.x || pos.y != mouse_focus.y) {
        move_t move = {mouse_focus, pos};
        validate_move(move);
        pos = move.second;
        input_queue.push(move);
        pending_move = false;
        if(print_log)
            cout << "Move to " << pos.x
                 << "x" << pos.y << endl;
    }
}
