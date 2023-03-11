#include "game/tile_lines.hpp"

using std::vector;


namespace game
{
    vector<Line> break_animation;
}


bool game::is_tile_in_line(Point target)
{
    for(Line const& line : break_animation) {
        if(line.progress > 0)
            for(auto const other : line.tiles)
                if(other == target)
                    return true;
    }

    return false;
}

