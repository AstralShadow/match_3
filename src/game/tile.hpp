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

    bool can_create_tile();
    Tile create_tile();


    /* Tile check ignore flags for is_tile_in_use */
    const u32 CHK_IGNORE_MOVING = 1;
    const u32 CHK_IGNORE_IN_LINE = 2;
    const u32 CHK_IGNORE_EMPTY = 4;
    const u32 CHK_IGNORE_FALLING = 8;
    const u32 CHK_IGNORE_LOCKED = 16;

    bool is_tile_in_use(Point, u32 ignore = 0);


    bool are_similar(Tile*, Tile*);
    bool is_tile_empty(Tile*);
    bool is_tile_empty(Point pos);
}

#endif // INCLUDE_GAME_TILE_HPP
