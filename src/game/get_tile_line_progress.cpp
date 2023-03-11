#include "game/tile_lines.hpp"

using std::vector;


float game::get_tile_line_progress(Point target)
{
    float highest = 0;
    for(Line const& line : break_animation) {
        if(line.progress > highest)
            for(auto const other : line.tiles)
                if(other == target)
                    highest = line.progress;
    }

    return highest;
}

