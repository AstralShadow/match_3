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
            render_tile(_rnd, tile, output);

            output.y += output.h;
        }

        output.x += output.w;
    }
}

void Board::render_tile(SDL_Renderer* _rnd,
                        tile_t* tile,
                        SDL_Rect output)
{
    auto color = get_color(tile);

    auto* state_ptr = get_state(tile);
    auto state = *state_ptr & STATE_MASK;
    auto animation = *state_ptr & ANIMATION_MASK;

    if(STATE_FALLING == state)
        output.y -= output.h * animation / 16;
    
    if(STATE_SWAPPING_LEFT == state)
        output.x -= output.w * (15 - animation) / 16;
    if(STATE_RETURNING_RIGHT == state)
        output.x -= output.w * animation / 16;

    if(STATE_SWAPPING_RIGHT == state)
        output.x += output.w * (15 - animation) / 16;
    if(STATE_RETURNING_LEFT == state)
        output.x += output.w * animation / 16;

    if(STATE_SWAPPING_UP == state)
        output.y -= output.h * (15 - animation) / 16;
    if(STATE_RETURNING_DOWN  == state)
        output.y -= output.h * animation / 16;

    if(STATE_SWAPPING_DOWN == state)
        output.y += output.h * (15 - animation) / 16;
    if(STATE_RETURNING_UP  == state)
        output.y += output.h * animation / 16;

    if(STATE_BREAKING == state)
    {
        int gray = 31;
        float rate = animation / 16.0f;
        color.r = color.r * rate + gray * (1.0f - rate);
        color.g = color.g * rate + gray * (1.0f - rate);
        color.b = color.b * rate + gray * (1.0f - rate);
    }


    SDL_SetRenderDrawColor(_rnd,
        color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_rnd, &output);

    if(_selected == tile)
    {
        color.r = 255 - color.r;
        color.g = 255 - color.g;
        color.b = 255 - color.b;

        SDL_SetRenderDrawColor(_rnd,
            color.r, color.g, color.b, color.a);

        output.x++; output.y++;
        output.w -= 2; output.h -= 2;
        SDL_RenderDrawRect(_rnd, &output);
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


