#include "game/skill.hpp"

void game::tick_skills(u32 time)
{
    auto itr = active_skills.begin();
    while(itr != active_skills.end()) {
        auto& skill = *itr;
        skill->tick(time);
        if(skill->is_done())
            itr = active_skills.erase(itr);
        else ++itr;
    }
}

