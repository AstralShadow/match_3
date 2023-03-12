#include "game/falling_tiles.hpp"
#include "game/board.hpp"


bool game::is_tile_falling(Point pos)
{
    for(auto const& group : falling_tiles) {
        if(group.tiles.size() < 2)
            continue;

        // Ignore top-most tile as it's meant
        //  for animation rendering purposes
        for(u32 i = 0; i < group.tiles.size() - 1; ++i)
            if(group.tiles[i] == pos)
                return true;
    }

    return false;
}

