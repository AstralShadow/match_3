#include "Engine.hpp"
#include "GameData.hpp"
#include <SDL2/SDL.h>
#include <algorithm>


void Engine::render()
{
    auto& _rnd = _renderer;

    SDL_SetRenderDrawColor(_rnd, 31, 31, 31, 255);
    SDL_RenderClear(_rnd);

    int w, h;
    SDL_GetRendererOutputSize(_rnd, &w, &h);
    int size = std::min(w, h);

    SDL_Rect board_area {
        (w - size) / 2,
        (h - size) / 2,
        size,
        size
    };
    _data->board.render(_rnd, board_area);
    
    SDL_RenderPresent(_rnd);
}

tile_t* Engine::get_tile_at(int x, int y)
{
    int w, h;
    SDL_GetRendererOutputSize(_renderer, &w, &h);
    int size= std::min(w, h);

    int tile_w = size / _data->board.w();
    int tile_h = size / _data->board.h();

    x -= (w - size) / 2;
    y -= (h - size) / 2;
    int tx = x / tile_w;
    int ty = y / tile_h;

    int board_w = _data->board.w();
    int board_h = _data->board.h();
    if(tx < 0) tx = 0;
    if(ty < 0) ty = 0;
    if(tx >= board_w) tx = board_w - 1;
    if(ty >= board_h) ty = board_h - 1;
    
    return _data->board(tx, ty);
}
