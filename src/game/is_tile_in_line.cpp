#include "game/line_animation.hpp"

using std::vector;


namespace game
{
    vector<LineAnimationData> break_animation;
}


bool game::is_tile_in_line(Point target)
{
    for(auto const& data : break_animation) {
        if(data.progress > 0)
            for(auto const other : data.line)
                if(other == target)
                    return true;
    }

    return false;
}

