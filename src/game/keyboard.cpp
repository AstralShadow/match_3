#include "game/game.hpp"
#include "core/core.hpp"
#include "config/keyboard.hpp"
#include "game/move_queue.hpp"
#include "utils/point.hpp"
#include "game/render.hpp" // keyboard_focus
#include "game/board.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>

using std::cout;
using std::endl;


template<const u8* keys, size_t count >
void when_key(u8 scancode, void (*callback)(void))
{
    for(size_t i = 0; i < count; i++)
        if(keys[i] == scancode) {
            callback();
            return;
        }
}

namespace game
{
    static const bool print_log = false;

    static bool selected = false;
    Point keyboard_focus {0, 0};

    static void kb_move_down();
    static void kb_move_up();
    static void kb_move_left();
    static void kb_move_right();
    static void kb_select();

    static void kb_fix_focus();
    static void kb_move_to(int dx, int dy);
}


void game::keydown(SDL_KeyboardEvent& ev, scene_uid)
{
    auto const& scancode = ev.keysym.scancode;
    if(scancode == SDL_SCANCODE_Q)
        core::stop();

    using namespace config;

#define _when_key(X) \
    when_key<X, sizeof(X) / sizeof(X[0])>

    _when_key(keys_left)(scancode, kb_move_left);
    _when_key(keys_right)(scancode, kb_move_right);
    _when_key(keys_up)(scancode, kb_move_up);
    _when_key(keys_down)(scancode, kb_move_down);

    _when_key(keys_select)(scancode, kb_select);

#undef _when_key

}


void game::kb_fix_focus()
{
    if(keyboard_focus.x < 0)
        keyboard_focus.x = 0;
    if(keyboard_focus.y < 0)
        keyboard_focus.y = 0;

    if(keyboard_focus.x > board.width - 1)
        keyboard_focus.x = board.width - 1;
    if(keyboard_focus.y > board.height - 1)
        keyboard_focus.y = board.height - 1;
}


void game::kb_move_left()
{
    kb_move_to(-1, 0);
    
    if(print_log)
        cout << "keyboard: left" << endl;
}

void game::kb_move_right()
{
    kb_move_to(1, 0);
    
    if(print_log)
        cout << "keyboard: right" << endl;
}

void game::kb_move_up()
{
    kb_move_to(0, -1);
    
    if(print_log)
        cout << "keyboard: up" << endl;
}

void game::kb_move_down()
{
    kb_move_to(0, 1);

    if(print_log)
        cout << "keyboard: down" << endl;
}


void game::kb_select()
{
    selected = !selected;
}


void game::kb_move_to(int dx, int dy)
{
    if(selected) {
        move_t move {keyboard_focus, keyboard_focus};

        keyboard_focus.y += dy;
        keyboard_focus.x += dx;
        kb_fix_focus();

        move.second = keyboard_focus;
        validate_move(move);
        input_queue.push(move);
    } else {
        keyboard_focus.y += dy;
        keyboard_focus.x += dx;
        kb_fix_focus();
    }
    selected = false;
}


