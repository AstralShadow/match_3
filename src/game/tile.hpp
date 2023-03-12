#ifndef INCLUDE_GAME_TILE_HPP
#define INCLUDE_GAME_TILE_HPP

#include "utils/types.hpp"
#include "utils/point.hpp"

namespace game
{
    struct Tile
    {
        u8 color = 0;
    };

    Tile create_tile();

    bool is_tile_in_use(Point);

    bool are_similar(Tile*, Tile*);
    bool is_tile_empty(Tile*);
    bool is_tile_empty(Point pos);
}

#endif // INCLUDE_GAME_TILE_HPP
