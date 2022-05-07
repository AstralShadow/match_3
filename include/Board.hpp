#ifndef INCLUDE_BOARD_HPP
#define INCLUDE_BOARD_HPP

#include <cstdint>
#include <cstddef>
#include <SDL2/SDL_rect.h>

struct SDL_Renderer;
typedef uint8_t tile_t;


class Board
{
public:
    Board(uint8_t w, uint8_t h);
    ~Board();

    uint8_t w() const { return _w; }
    uint8_t h() const { return _h; }
    size_t size() const { return _w * _h; }

    tile_t* operator ()(uint8_t x, uint8_t y);

    void render(SDL_Renderer*, SDL_Rect);

    SDL_Color get_color(tile_t*) const;

private:
    uint8_t _w, _h;
    tile_t* _tiles;

};

#endif // INCLUDE_BOARD_HPP
