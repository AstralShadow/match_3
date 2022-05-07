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

