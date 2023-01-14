#ifndef INCLUDE_TILE_HPP
#define INCLUDE_TILE_HPP

#include "utils/types.hpp"

namespace game
{
    struct Tile
    {
        u8 color;
        //int animation_end = 0;
        
    };

    Tile create_tile();
}

#endif // INCLUDE_TILE_HPP
