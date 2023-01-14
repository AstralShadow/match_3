#ifndef INCLUDE_RENDER_HPP
#define INCLUDE_RENDER_HPP

#include <SDL2/SDL_rect.h>

namespace game
{
    struct Tile;

    extern SDL_Rect board_area;


    void render_board();
    void render_tile(Tile* tile, SDL_Rect output);
};

#endif // INCLUDE_RENDER_HPP
