#include "game/game.hpp"
#include "game/render.hpp"
#include "game/board.hpp"
#include "core/core.hpp"
#include "utils/point.hpp"
#include <SDL2/SDL_render.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
EM_JS(int, canvas_get_width, (), {
    return document.getElementById("canvas").offsetWidth;
});
EM_JS(int, canvas_get_height, (), {
    return document.getElementById("canvas").offsetHeight;
});
#endif

static auto& rnd = core::renderer;


namespace game
{
    SDL_Rect board_area { 0, 0, 800, 500 };

    Point screen;
}


void game::render_resize()
{
#ifdef __EMSCRIPTEN__
    screen.x = canvas_get_width();
    screen.y = canvas_get_height();
    SDL_SetWindowSize(core::window, screen.x, screen.y);
#else
    SDL_GetRendererOutputSize(rnd, &screen.x, &screen.y);
#endif

    float ratio = board.width * 1.0f / board.height;
    board_area.w = static_cast<int>(std::min<float>(
        screen.x,
        screen.y * ratio
    ));
    board_area.h = board_area.w / ratio;
    board_area.x = screen.x - board_area.w;
    //board_area.y = (screen.y - board_area.w) / 2;
}

