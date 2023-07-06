#include "game/falling_tiles.hpp"
#include "game/board.hpp"
#include "config/game.hpp"

using std::vector;


namespace game
{
    static vector<Point>
    find_filling_path(Point pos, bool can_diagonal);
}


/* Find any gaps from bottom to top.
 * When a gap is found,
 *  find a path of tiles that can fall there.
 * Prefer vertical paths. */

void game::activate_falling_tiles()
{
    for(int y = board.height - 1; y >= 0; --y)
    for(int diagonal = 0; diagonal < 2; ++diagonal)
    for(int x = 0; x < board.width; ++x) {
        if(diagonal && !config::permit_diagonal_falling)
            continue;

        Point pos {x, y};
        if(!is_tile_empty(pos))
            continue;
        if(is_tile_in_use(pos, CHK_IGNORE_EMPTY))
            continue;

        auto path = find_filling_path(pos, diagonal);

        for(u32 i = 1; i < path.size(); i++) {
            auto* bottom_tile = get_tile(path[i - 1]);
            auto* top_tile = get_tile(path[i]);
            std::swap(*bottom_tile, *top_tile);
        }

        if(path.back().y == 0 && can_create_tile()) {
            *get_tile(path.back()) = create_tile();
            path.push_back({path.back().x, -1});
        }

        if(path.size() == 1)
            continue;

        falling_tiles.push_back({path});
    }
}

vector<Point>
game::find_filling_path(Point pos, bool can_diagonal)
{
    vector<Point> path {pos};

    while(pos.y != 0) {
        vector<Point> src;
        src.push_back({pos.x, pos.y - 1});

        using config::permit_diagonal_falling;
        if(permit_diagonal_falling && can_diagonal) {
            src.push_back({pos.x + 1, pos.y - 1});
            src.push_back({pos.x - 1, pos.y - 1});
        }

        for(auto next : src) {
            if(is_tile_in_use(next))
                continue;
            path.push_back(next);
            break;
        }

        if(pos == path.back()) // nothing inserted
            break;
        pos = path.back();
    }

    return path;
}

