#ifndef INCLUDE_BOARD_HPP
#define INCLUDE_BOARD_HPP

#include <cstdint>
#include <cstddef>
#include <SDL2/SDL_rect.h>

struct SDL_Renderer;
typedef uint8_t tile_t;

const uint16_t TARGET_BOARD_TICKRATE = 90;

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


    uint8_t* get_state(tile_t*);
    tile_t* operator ()(uint8_t x, uint8_t y);


    void select(tile_t*);
    tile_t* get_selected() { return _selected; }
    void move(tile_t*);
    void swap(tile_t*, tile_t*, bool animated = false);


    void tick(uint8_t progress = 1);
    /** Returns if a match was detected. */
    bool check_all();
    bool check(tile_t*);

    void render(SDL_Renderer*, SDL_Rect);
    void render_tile(SDL_Renderer*, tile_t*, SDL_Rect);

    SDL_Color get_color(tile_t*) const;
    SDL_Color get_color(uint8_t type) const;


    /** State data
     *  ______________ __________________
     * |              |                  |
     * | 4bit - state | 4bit - animation |
     * |______________|__________________|
     * 
     */
    enum : uint8_t {
        ANIMATION_MASK          = 0x0f,
        STATE_MASK              = 0xf0,
        STATE_NORMAL            = 0 << 4,
        STATE_BREAKING          = 1 << 4,
        STATE_FALLING           = 2 << 4,

        STATE_SWAPPING_LEFT     = 3 << 4,
        STATE_RETURNING_RIGHT   = 4 << 4,
        STATE_SWAPPING_UP       = 5 << 4,
        STATE_RETURNING_DOWN    = 6 << 4,
        STATE_SWAPPING_DOWN     = 7 << 4,
        STATE_RETURNING_UP      = 8 << 4,
        STATE_SWAPPING_RIGHT    = 9 << 4,
        STATE_RETURNING_LEFT    = 10 << 4,

        STATE_SWAPPING_TO_RETURNING = 1 << 4
    };

    /**  Tile data:
     *  ______________ ______________ _____________
     * |              |              |             |
     * | 3bit - extra | 1bit - bonus | 4bit - type |
     * |______________|______________|_____________|
     *
     */
    enum : tile_t {
        TILE_TYPE_MASK = 0x0f,

        TILE_BONUS = 0x10,
    };


    void assign_score(tile_t*, int combo);    
    double _color_score[TILE_TYPE_MASK] {0};
    uint8_t _last_type = 0;
    uint32_t _total_color_combo = 0;

private:
    uint8_t _w, _h;
    tile_t* _selected = nullptr;

    tile_t* _tiles = nullptr;

    uint8_t* _state = nullptr;

    void fill(tile_t* tile);
};

#endif // INCLUDE_BOARD_HPP
