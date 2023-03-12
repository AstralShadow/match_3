#include "game/falling_tiles.hpp"
#include "game/board.hpp"


bool game::is_tile_falling(Point pos)
{
    for(auto const& group : falling_tiles) {
        for(auto const& other : group.tiles)
            if(other == pos)
                return true;
    }

    return false;
}

