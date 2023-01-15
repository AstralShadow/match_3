#ifndef INCLUDE_RENDER_HPP
#define INCLUDE_RENDER_HPP

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
};

#endif // INCLUDE_RENDER_HPP
