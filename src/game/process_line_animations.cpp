#include "game/line_animation.hpp"
#include "game/board.hpp"
#include "config/game.hpp"


void game::process_line_animations(int ms)
{
    float time = ms * 1.0f / config::break_duration;

    auto itr = break_animation.begin();
    while(itr != break_animation.end()) {
        itr->progress += time;
        if(itr->progress > 1) {
            finish_line_animation(&*itr);
            itr = break_animation.erase(itr);
        } else ++itr;
    }
}

