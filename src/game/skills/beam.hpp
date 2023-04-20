#ifndef INCLUDE_GAME_SKILL_BEAM_HPP
#define INCLUDE_GAME_SKILL_BEAM_HPP

#include "game/skill.hpp"
#include <vector>


namespace game
{
    // Clears tiles in a line
    class Beam : public Skill
    {
        Point pos;
        Point direction;

        std::vector<Point> tiles;
        std::vector<int> tile_progress;

    public:
        Beam(Point pos, Point direction);

        void tick(u32 time) override;
        bool is_locked(Point tile) override;
        bool is_done() override;

        bool apply_tile_anim(Point tile,
                             SDL_Rect& out) override;

    private:
        void find_targets();

    };
}

#endif // INCLUDE_GAME_SKILL_BEAM_HPP
