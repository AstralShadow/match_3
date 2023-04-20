#include "game/tile.hpp"
#include "game/skill.hpp"


bool game::is_tile_locked(Point pos)
{
    for(auto& skill : active_skills)
        if(skill->is_locked(pos))
            return true;

    return false;
}

