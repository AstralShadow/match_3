#include "Engine.hpp"
#include "GameData.hpp"
#include <SDL2/SDL.h>
#include <algorithm>


void Engine::render()
{
    auto& _rnd = _renderer;

    SDL_SetRenderDrawColor(_rnd, 0, 0, 0, 255);
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


    SDL_Point score_area_size {
        board_area.x,
        h
    };

    int bars_y = 2; 
    
    SDL_Rect score_area {
        0, 0,
        score_area_size.x / 2,
        score_area_size.y / bars_y
    };
    int score_bar = 0;

    static double delayed_score[16] {0};
    for(int t = 0; t < Board::TILE_TYPE_MASK; t++)
    {
        auto real_score = _data->board._color_score[t];
        delayed_score[t] *= 4;
        delayed_score[t] += real_score;
        delayed_score[t] /= 5;
        auto score = delayed_score[t];

        if(score < 1) continue;
        score_bar++;

        SDL_Rect score_rect {
            score_area.w / 2 - 10,
            20 + score_area.h * (score_bar - 1) / 2,
            20,
            score_area.h - 40
        };
        if(score_bar % 2)
            score_rect.x += score_area.w;
        if(score_bar + 1 > bars_y * 2)
        {
            score_rect.y -= score_area.h * bars_y;
            score_rect.y += score_area.h / 2;
            score_rect.x += score_area.w * 2 + board_area.w;
        }

        auto color = _data->board.get_color(t);
        SDL_Color color1 {
            (uint8_t) ((color.r + 0) / 2),
            (uint8_t) ((color.g + 0) / 2),
            (uint8_t) ((color.b + 0) / 2),
            255
        };
        SDL_Color color2 {
            (uint8_t) ((color.r + 255) / 2),
            (uint8_t) ((color.g + 255) / 2),
            (uint8_t) ((color.b + 255) / 2),
            255
        };
        

        double bar_size = 250.0;

        auto filled = score;
        while(filled > bar_size) filled -= bar_size;
        filled = filled / bar_size;
        auto h = score_rect.h;
        auto filled_h = h * filled;


        SDL_SetRenderDrawColor(_rnd,
            color1.r, color1.g, color1.b, color1.a);

        score_rect.h = h - filled_h + 1;
        SDL_RenderFillRect(_rnd, &score_rect);


        SDL_SetRenderDrawColor(_rnd,
            color2.r, color2.g, color2.b, color2.a);
    
        score_rect.y += score_rect.h;
        score_rect.h = filled_h;
        SDL_RenderFillRect(_rnd, &score_rect);
    }

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
