#include "game/game.hpp"
#include "core/core.hpp"
#include "utils/point.hpp"
#include "game/render.hpp"
#include "game/board.hpp"
#include "game/move_queue.hpp"
#include "game/line_sequence.hpp"
#include "game/skills/beam.hpp"
#include "config/controls.hpp"
#include <SDL2/SDL_events.h>

using ButtonEv = SDL_MouseButtonEvent;
using MotionEv = SDL_MouseMotionEvent;

static Point mouse_focus {0, 0};
static bool pending_move = false;

Point game::get_board_pos(int x, int y)
{
    return {
        (x - board_area.x) * board.width / board_area.w,
        (y - board_area.y) * board.height / board_area.h
    };
}


void game::mousedown(ButtonEv& ev, scene_uid)
{
    mouse_focus = get_board_pos(ev.x, ev.y);
    pending_move = true;
}

void game::mouseup(ButtonEv& ev, scene_uid)
{
    if(!pending_move)
        return;

    move_t move {
        mouse_focus, get_board_pos(ev.x, ev.y),
        &line_sequences[sequences_count - 1]
    };
    validate_move(move);
    if(ev.button == SDL_BUTTON_LEFT) {
        equeue_move(move);
    } else if (ev.button == SDL_BUTTON_RIGHT) {
        active_skills.push_back(std::make_unique
            <Beam>(move.first,
                   move.second - move.first));
    }

    pending_move = false;
}

void game::mouse_motion(MotionEv& ev,
                        scene_uid)
{
    if(!pending_move || !config::quick_draw)
        return;

    Point pos = get_board_pos(ev.x, ev.y);
    if(pos != mouse_focus) {
        move_t move = {
            mouse_focus, pos,
            &line_sequences[sequences_count - 1]
        };
        validate_move(move);
        if(ev.state & SDL_BUTTON_LMASK) {
            equeue_move(move);
        } else if (ev.state & SDL_BUTTON_RMASK) {
            active_skills.push_back(std::make_unique
                <Beam>(move.first,
                       move.second - move.first));
        }

        pending_move = false;
    }
}
