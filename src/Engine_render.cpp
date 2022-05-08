#include "Engine.hpp"
#include "GameData.hpp"
#include <SDL2/SDL.h>


void Engine::render()
{
    auto& _rnd = _renderer;

    SDL_SetRenderDrawColor(_rnd, 31, 31, 31, 255);
    SDL_RenderClear(_rnd);

    SDL_Rect board_area {
        (WIDTH - HEIGHT) / 2,
        0,
        HEIGHT,
        HEIGHT
    };
    _data->board.render(_rnd, board_area);
    
    SDL_RenderPresent(_rnd);
}

tile_t* Engine::get_tile_at(int x, int y)
{
    int tile_w = HEIGHT / _data->board.w();
    int tile_h = HEIGHT / _data->board.h();

    x -= (WIDTH - HEIGHT) / 2;
    int tx = x / tile_w;
    int ty = y / tile_h;
    return _data->board(tx, ty);
}
