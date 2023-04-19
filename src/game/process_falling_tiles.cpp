#include "game/falling_tiles.hpp"
#include "game/board.hpp"
#include "game/line_animation.hpp"
#include "config/game.hpp"

namespace game
{
    // Used when not detecting lines while falling
    static vector<Point> line_detection_queue;
}


void game::process_falling_tiles(int ms)
{
    if(config::detect_lines_when_falling) {
        process_falling_tiles_activation(ms);
        process_falling_tiles_progress(ms);
    } else {
        process_falling_tiles_progress(ms);
        process_falling_tiles_activation(ms);

        for(auto pos : line_detection_queue)
            if(!is_tile_in_use(pos))
                detect_lines(pos);

        line_detection_queue.clear();
    }

}

void game::process_falling_tiles_activation(int ms)
{
    if(!config::falling_only_when_board_idle) {
        activate_falling_tiles();
        return;
    }

    static int activation_timer = 0;

    if(break_animation.size() > 0)
        activation_timer = 0;
    else
        activation_timer += ms;

    if(activation_timer >= config::fall_delay)
        activate_falling_tiles();
}

void game::process_falling_tiles_progress(int ms)
{
    float time = ms * 1.0f / config::fall_duration;

    if(config::slower_massive_falls) {
        int count;
        if(config::slower_massive_falls_based_on_lines)
            count = count_falling_lines();
        else
            count = count_falling_tiles();
        auto rate = config::slowness_per_falling_tile;
        time *= 1.0f - count * rate;
    }

    // Store size in variable so any reappended
    //  elements don't get iterated
    u32 size = falling_tiles.size();
    for(u32 i = 0; i < size; ++i) {
        auto& group = falling_tiles[i];
        group.progress += time;
        group.age += time;

        if(group.progress >= 1) {
            auto group_copy = group;

            auto pos = falling_tiles.begin() + i;
            falling_tiles.erase(pos);

            finish_fall(group_copy);

            i--;
            size--;
        }
    }
}

void game::finish_fall(FallingTiles group)
{
    auto bottom = group.tiles.front();
    group.tiles.erase(group.tiles.begin());

    if(group.tiles.size() > 1) {
        group.progress -= config::fall_delay_factor;

        if(group.tiles.size() > 1)
            falling_tiles.push_back(group);
    }

    if(bottom.y == -1)
        return;

    if(config::detect_lines_when_falling)
        detect_lines(bottom);
    else
        line_detection_queue.push_back(bottom);
}

