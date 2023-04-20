#ifndef INCLUDE_GAME_SKILL_HPP
#define INCLUDE_GAME_SKILL_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include <vector>


namespace game
{

    class Skill
    {
    protected:
        Skill() = default;
    public:
        virtual ~Skill() = default;

        virtual void tick(u32 time);
        virtual bool is_locked(Point tile);
        virtual bool is_done() = 0;
    };

    extern std::vector<Skill*> active_skills;


    bool is_tile_locked(Point pos);
}

#endif // INCLUDE_GAME_SKILL_HPP
