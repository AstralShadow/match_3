#ifndef INCLUDE_GAME_TILE_HPP
#define INCLUDE_GAME_TILE_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"

namespace game
{
    struct Tile
    {
        u8 color;
    };

    Tile create_tile();

    bool is_tile_in_use(Point);
}

#endif // INCLUDE_GAME_TILE_HPP
