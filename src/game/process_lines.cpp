#include "game/tile_lines.hpp"
#include "game/board.hpp"
#include "config/game.hpp"


void game::process_lines(int ms)
{
    float time = ms * 1.0f / config::break_duration;

    auto itr = break_animation.begin();
    while(itr != break_animation.end()) {
        itr->progress += time;
        if(itr->progress > 1) {
            remove_line(&*itr);
            itr = break_animation
                .erase(itr);
        } else ++itr;
    }
}

void game::remove_line(Line* line)
{
    // TODO scoring

    for(Point pos : line->tiles)
        remove_tile(pos);
}

