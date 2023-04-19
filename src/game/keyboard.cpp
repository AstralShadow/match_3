#include "game/game.hpp"
#include "game/keyboard.hpp"
#include "core/core.hpp"
#include "config/keyboard.hpp"
#include "game/move_queue.hpp"
#include "utils/point.hpp"
#include "game/board.hpp"
#include <SDL2/SDL_events.h>
#include <iostream>

using std::cout;
using std::endl;

using config::keys_action;
using config::keys_left;
using config::keys_right;
using config::keys_up;
using config::keys_down;


template<const u8* keys, size_t count >
void when_key(u8 scancode, void (*callback)(int))
{
    for(size_t i = 0; i < count; i++)
        if(keys[i] == scancode) {
            auto state = game::kb_players[i].state;

            game::kb_players[i].visibility_time
                = config::kb_player_visibility_time;

            // Skip rotation animations when empty pess
            if(state == game::KB_FOCUS_DIAGONAL)
                game::kb_players[i].visibility_time
                    -= config::kb_diagonal_rotation_time;

            callback(i);
            return;
        }
}

namespace game
{
    static const bool print_log = false;

    KBPlayer kb_players[config::max_kb_players];

    static void kb_move_down(int player);
    static void kb_move_up(int player);
    static void kb_move_left(int player);
    static void kb_move_right(int player);
    static void kb_action(int player);

    static void kb_fix_focus(int player);
    static void kb_move_by(int player, int dx, int dy);
}


void game::keydown(SDL_KeyboardEvent& ev, scene_uid)
{
    auto const& scancode = ev.keysym.scancode;
    if(scancode == SDL_SCANCODE_Q)
        core::stop();

#define _when_key(X) \
    when_key<X, sizeof(X) / sizeof(X[0])>

    _when_key(keys_left)(scancode, kb_move_left);
    _when_key(keys_right)(scancode, kb_move_right);
    _when_key(keys_up)(scancode, kb_move_up);
    _when_key(keys_down)(scancode, kb_move_down);

    _when_key(keys_action)(scancode, kb_action);

#undef _when_key

}


void game::kb_fix_focus(int _player)
{
    auto& player = kb_players[_player];

    if(player.pos.x < 0)
        player.pos.x = 0;
    if(player.pos.y < 0)
        player.pos.y = 0;

    if(player.pos.x > board.width - 1)
        player.pos.x = board.width - 1;
    if(player.pos.y > board.height - 1)
        player.pos.y = board.height - 1;
}


void game::kb_move_left(int _player)
{
    auto const& player = kb_players[_player];
    if(player.state != KB_FOCUS_DIAGONAL) {
        kb_move_by(_player, -1, 0);
    } else {
        const u8* keys = SDL_GetKeyboardState(nullptr);
        if(keys[keys_up[_player]])
            kb_move_by(_player, -1, -1);
        else if(keys[keys_down[_player]])
            kb_move_by(_player, -1, 1);
    }
    
    if(print_log)
        cout << "keyboard[" << _player << "]: left"
             << endl;
}

void game::kb_move_right(int _player)
{
    auto const& player = kb_players[_player];
    if(player.state != KB_FOCUS_DIAGONAL) {
        kb_move_by(_player, 1, 0);
    } else {
        const u8* keys = SDL_GetKeyboardState(nullptr);
        if(keys[keys_up[_player]])
            kb_move_by(_player, 1, -1);
        else if(keys[keys_down[_player]])
            kb_move_by(_player, 1, 1);
    }
    
    if(print_log)
        cout << "keyboard[" << _player << "]: right"
             << endl;
}

void game::kb_move_up(int _player)
{
    auto const& player = kb_players[_player];
    if(player.state != KB_FOCUS_DIAGONAL) {
        kb_move_by(_player, 0, -1);
    } else {
        const u8* keys = SDL_GetKeyboardState(nullptr);
        if(keys[keys_left[_player]])
            kb_move_by(_player, -1, -1);
        else if(keys[keys_right[_player]])
            kb_move_by(_player, 1, -1);
    }
    
    if(print_log)
        cout << "keyboard[" << _player << "]: up"
             << endl;
}

void game::kb_move_down(int _player)
{
    auto const& player = kb_players[_player];
    if(player.state != KB_FOCUS_DIAGONAL) {
        kb_move_by(_player, 0, 1);
    } else {
        const u8* keys = SDL_GetKeyboardState(nullptr);
        if(keys[keys_left[_player]])
            kb_move_by(_player, -1, 1);
        else if(keys[keys_right[_player]])
            kb_move_by(_player, 1, 1);
    }

    if(print_log)
        cout << "keyboard[" << _player << "]: down"
             << endl;
}


void game::kb_action(int _player)
{
    auto& player = kb_players[_player];
    switch(player.state) {
    case KB_IDLE:
        player.state = KB_FOCUS;
        break;
    case KB_FOCUS:
        player.state = KB_FOCUS_DIAGONAL;
        break;
    case KB_FOCUS_DIAGONAL:
        player.state = KB_IDLE;
        break;
    }
}


void game::kb_move_by(int _player, int dx, int dy)
{
    auto& player = kb_players[_player];


    switch(player.state) {

        case KB_IDLE: {
            player.pos.y += dy;
            player.pos.x += dx;
            kb_fix_focus(_player);
            break;
        }

        case KB_FOCUS_DIAGONAL:
        case KB_FOCUS: {
            move_t move {
                player.pos, player.pos,
                &line_sequences[_player]
            };

            player.pos.y += dy;
            player.pos.x += dx;
            kb_fix_focus(_player);

            move.second = player.pos;
            validate_move(move);
            equeue_move(move);

            break;
        }

    }

    player.state = KB_IDLE;
}


void game::fade_unused_keyboard_players(int ms)
{
    for(auto& player : kb_players)
        if(player.visibility_time > 0)
            player.visibility_time -= ms;
}

