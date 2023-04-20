#include "game/skill.hpp"

using game::Skill;

namespace game
{
    std::vector<Skill*> active_skills;
}


void Skill::tick(u32)
{ }

bool Skill::is_locked(Point)
{
    return false;
}

