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
    Board(Board const&);
    void operator =(Board const&);
    Board(Board&&);
    ~Board();


    uint8_t w() const { return _w; }
    uint8_t h() const { return _h; }
    size_t size() const { return _w * _h; }

    void select(tile_t*);
    tile_t* get_selected() { return _selected; }
    void move(tile_t*);
    void swap(tile_t*);

    void check_groups();
    uint8_t* get_state(tile_t*);

    tile_t* operator ()(uint8_t x, uint8_t y);

    void tick(uint8_t progress = 1);
    void render(SDL_Renderer*, SDL_Rect);
    void render_tile(SDL_Renderer*, tile_t*, SDL_Rect);

    SDL_Color get_color(tile_t*) const;


    enum : uint8_t {
        ANIMATION_MASK = 15,
        STATE_MASK = 240,
        STATE_NORMAL = 0,
        STATE_BREAKING = 16,
        STATE_FALLING = 32,
    };

private:
    uint8_t _w, _h;
    tile_t* _tiles = nullptr;
    tile_t* _selected = nullptr;

    uint8_t* _state = nullptr;
    /*  ______________ _________________
     * |              |                 |
     * | 4bit - state | 4bit - cooldown |
     * |______________|_________________|
     *  
     * States
     * 0 - normal, moveable.
     * 1 - breaking
     * 2 - falling from up
     */

    void fill(tile_t* tile);
};

#endif // INCLUDE_BOARD_HPP
