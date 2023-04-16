#include "game/falling_tiles.hpp"


int game::count_falling_tiles()
{
    int count = 0;
    for(auto const& group : falling_tiles)
        if(group.age > 0 && group.age < 1)
            count += group.tiles.size() - 1;

    return count;
}

