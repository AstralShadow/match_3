#ifndef INCLUDE_GAME_LINE_ANIMATION_HPP
#define INCLUDE_GAME_LINE_ANIMATION_HPP

#include "game/tile.hpp"
#include "game/line.hpp"
#include <vector>


namespace game
{
    using std::vector;

    struct LineSequence;

    struct LineAnimationData
    {
        Line line;
        LineSequence* sequence = nullptr;

        float progress = 0; // [0, 1]
    };

    // Stores detected lines
    extern vector<LineAnimationData> break_animation;

    // Detects and stores new lines.
    // Returns true if a line is found and stored
    bool detect_lines(Point, LineSequence* = nullptr);

    bool is_tile_in_line(Point);
    float get_line_animation_progress(Point);

    void process_line_animations(int);
    void finish_line_animation(LineAnimationData*);
}

#endif // INCLUDE_GAME_TILE_ANIMATION_HPP
