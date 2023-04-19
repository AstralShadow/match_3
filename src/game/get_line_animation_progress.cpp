#include "game/line_animation.hpp"

using std::vector;


float game::get_line_animation_progress(Point target)
{
    float highest = 0;
    for(auto const& data : break_animation) {
        if(data.progress > highest)
            for(auto const other : data.line)
                if(other == target)
                    highest = data.progress;
    }

    return highest;
}

