#include "game/render.hpp"
#include "game/board.hpp"
#include "game/falling_tiles.hpp"
#include "config/game.hpp"


bool game::apply_tile_fall_anim(Point pos,
                                SDL_Rect& output)
{
    SDL_Point size {
        board_area.w / board.width,
        board_area.h / board.height
    };

    for(auto const& group : falling_tiles)
    for(u32 i = 0; i < group.tiles.size() - 1; ++i) {
        if(pos != group.tiles[i])
            continue;

        Point source = group.tiles[i + 1];
        Point delta {
            pos.x - source.x,
            pos.y - source.y
        };

        auto progress = 1 - group.progress;
        float delay = i * config::fall_delay_factor;
        if(delay > group.age)
            delay = group.age;
        progress += delay;

        output.x -= delta.x * size.x * progress;
        output.y -= delta.y * size.y * progress;
        return true;
    }

    return false;
}

