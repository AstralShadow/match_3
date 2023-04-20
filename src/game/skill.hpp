#ifndef INCLUDE_GAME_SKILL_HPP
#define INCLUDE_GAME_SKILL_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"
#include <vector>
#include <memory>

using std::unique_ptr;


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

        virtual bool apply_tile_anim(Point tile,
                                     SDL_Rect& output);
    };

    extern std::vector<unique_ptr<Skill>> active_skills;


    void tick_skills(u32 time);


    bool is_tile_locked(Point pos);
}

#endif // INCLUDE_GAME_SKILL_HPP
