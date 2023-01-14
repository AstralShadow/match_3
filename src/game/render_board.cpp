#include "game/render.hpp"
#include "game/board.hpp"


void game::render_board()
{
    SDL_Rect output {
        board_area.x,
        board_area.y,
        board_area.w / board.width,
        board_area.h / board.height
    };

    for(int y = 0; y < board.height; y++)
    for(int x = 0; x < board.width; x++) {
        auto tile = get_tile(x, y);

        output.x = board_area.x + output.w * x;
        output.y = board_area.y + output.h * y;

        render_tile(tile, output);
    }
}
