#ifndef INCLUDE_GAME_RENDER_HPP
#define INCLUDE_GAME_RENDER_HPP

#include <SDL2/SDL_rect.h>
#include "utils/point.hpp"

namespace game
{
    struct Tile;

    extern SDL_Rect board_area;


    // Transforms pixels to tile pos
    Point get_board_pos(int x, int y);

    void render_board();
    void render_tile(Tile* tile, SDL_Rect output);
    void render_tile_focus_frame(SDL_Rect output);

    bool apply_tile_animation(Point pos,
                              SDL_Rect& output);
    bool apply_tile_move_anim(Point pos,
                              SDL_Rect& output);
    bool apply_tile_fall_anim(Point pos,
                              SDL_Rect& output);

    extern Point keyboard_focus;
};

#endif // INCLUDE_GAME_RENDER_HPP
