#include "game/skill.hpp"

using game::Skill;

namespace game
{
    std::vector<unique_ptr<Skill>> active_skills;
}


void Skill::tick(u32)
{ }

bool Skill::is_locked(Point)
{
    return false;
}


bool Skill::apply_tile_anim(Point, SDL_Rect&)
{
    return false;
}

