#include "Board.hpp"
#include <SDL2/SDL.h>

void Board::render(SDL_Renderer* _rnd, SDL_Rect area)
{
    SDL_Rect output {
        area.x,
        area.y,
        area.w / _w,
        area.h / _h
    };

    for(int x = 0; x < _w; x++)
    {
        output.y = area.y;
        for(int y = 0; y < _h; y++)
        {
            tile_t* tile = (*this)(x, y);

            auto color = get_color(tile);
            SDL_SetRenderDrawColor(_rnd,
                color.r, color.g, color.b, color.a);

            SDL_RenderFillRect(_rnd, &output);

            output.y += output.h;
        }

        output.x += output.w;
    }
}


SDL_Color Board::get_color(tile_t* tile) const
{
    if(tile)
        switch(*tile)
        {
            case 0: return {   0,   0,   0, 255};
            case 1: return { 255,   0,   0, 255};
            case 2: return {   0, 255,   0, 255};
            case 3: return {   0,   0, 255, 255};
            case 4: return { 255, 255,   0, 255};
            case 5: return {   0, 255, 255, 255};
            case 6: return { 255,   0, 255, 255};
            case 7: return { 255, 255, 255, 255};
        }

    return {127, 127, 127, 255};
}


