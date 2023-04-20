#include "game/render.hpp"
#include "game/skill.hpp"


bool game::apply_tile_skill_anim(Point pos,
                                 SDL_Rect& output)
{
    for(auto& skill : active_skills)
        if(skill->apply_tile_anim(pos, output))
            return true;

    return false;
}

