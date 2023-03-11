#ifndef INCLUDE_GAME_TILE_LINES_HPP
#define INCLUDE_GAME_TILE_LINES_HPP

#include "game/tile.hpp"
#include <vector>


namespace game
{

    struct Line
    {
        std::vector<Point> tiles;
        float process = 0; // [0, 1]
    };

    // Stores detected lines
    extern std::vector<Line> break_animation;

    // Detects and stores new lines that contain a given tile.
    // Returns true if a line is found and stored
    bool detect_lines(Point);

    bool is_tile_in_line(Point);
}

#endif // INCLUDE_GAME_TILE_LINES_HPP
