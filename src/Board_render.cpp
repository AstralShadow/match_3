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
            if(_focused == tile)
                render_focus_frame(_rnd, output);

            output.y += output.h;
        }

        output.x += output.w;
    }
}

void Board::render_tile(SDL_Renderer* _rnd,
                        tile_t* tile,
                        SDL_Rect output)
{
    SDL_Color color = get_color(tile);
    SDL_Color bonus_color{0, 0, 0, 255};


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
        bonus_color.r = bonus_color.r * rate
            + gray * (1.0f - rate);
        bonus_color.g = bonus_color.g * rate
            + gray * (1.0f - rate);
        bonus_color.b = bonus_color.b * rate
            + gray * (1.0f - rate);
    }


    SDL_SetRenderDrawColor(_rnd,
        color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_rnd, &output);

    if(_selected == tile)
    {
        SDL_Color border_color;
        border_color.r = 255 - color.r;
        border_color.g = 255 - color.g;
        border_color.b = 255 - color.b;
        border_color.a = color.a;

        SDL_Rect border {
            output.x + 1,
            output.y + 1,
            output.w - 2,
            output.h - 2
        };

        SDL_SetRenderDrawColor(_rnd,
            border_color.r, border_color.g,
            border_color.b, border_color.a);

        SDL_RenderDrawRect(_rnd, &border);
        border.x++;
        border.y++;
        border.w -= 2;
        border.h -= 2;
        SDL_RenderDrawRect(_rnd, &border);
    }

    if(*tile & TILE_BONUS)
    {
        SDL_Rect border {
            output.x + output.w * 3 / 10,
            output.y + output.h * 3 / 10,
            output.w * 2 / 5,
            output.h * 2 / 5
        };

        SDL_SetRenderDrawColor(_rnd,
            bonus_color.r, bonus_color.g,
            bonus_color.b, bonus_color.a);

        SDL_RenderFillRect(_rnd, &border);
    }
}

SDL_Color Board::get_color(tile_t* tile) const
{
    if(tile)
        return get_color(*tile & TILE_TYPE_MASK);

    return {127, 127, 127, 255};
}

SDL_Color Board::get_color(uint8_t type) const
{
    switch(type & TILE_TYPE_MASK)
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


void Board::render_focus_frame(SDL_Renderer* _rnd,
                               SDL_Rect output)
{
    SDL_SetRenderDrawColor(_rnd, 0, 0, 0, 255);
    
    for(int i = 0; i < 2; i++)
    {
        output.x++;
        output.y++;
        output.w -= 2;
        output.h -= 2;
        SDL_RenderDrawRect(_rnd, &output);
    }
}
