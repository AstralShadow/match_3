#include "game/render.hpp"
#include "game/board.hpp"
#include "game/keyboard.hpp"
#include "utils/pi.hpp"
#include "utils/point.hpp"


void game::render_board()
{
    Point tile_size {
        board_area.w / board.width,
        board_area.h / board.height
    };

    for(int y = 0; y < board.height; y++)
    for(int x = 0; x < board.width; x++) {
        auto tile = get_tile(x, y);

        SDL_Rect output {
            board_area.x + tile_size.x * x,
            board_area.y + tile_size.y * y,
            tile_size.x,
            tile_size.y
        };

        apply_tile_animation({x, y}, output);

        render_tile(tile, output);
    }

    render_board_overlay();
}

void game::render_board_overlay()
{
    using config::kb_player_visibility_time;
    using config::kb_fade_blinks;
    auto const kb_max_vtime = kb_player_visibility_time;


    Point tile_size {
        board_area.w / board.width,
        board_area.h / board.height
    };

    for(int y = 0; y < board.height; y++)
    for(int x = 0; x < board.width; x++) {
        SDL_Rect output {
            board_area.x + tile_size.x * x,
            board_area.y + tile_size.y * y,
            tile_size.x,
            tile_size.y
        };

        for(auto const& player : kb_players) {
            auto vtime = player.visibility_time;
            if(vtime < 1)
                continue;

            float opacity = 1;

            if(vtime < kb_max_vtime / 3) {
                opacity = vtime / (kb_max_vtime / 3.0f);
                opacity = (cos(
                    (1 - opacity) * pi_f() *
                    (kb_fade_blinks * 2 + 1)
                ) + 1) / 2;
            }

            if(player.pos.x == x && player.pos.y == y) {
                render_tile_focus_frame(output,
                                        player,
                                        255 * opacity);
                break; 
            }
        }
    }

}

