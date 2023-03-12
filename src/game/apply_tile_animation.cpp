#include "game/render.hpp"
#include "game/board.hpp"


bool game::apply_tile_animation(Point pos,
                                SDL_Rect& output)
{
    if(apply_tile_move_anim(pos, output))
        return true;

    if(apply_tile_fall_anim(pos, output))
        return true;

    return false;
}

