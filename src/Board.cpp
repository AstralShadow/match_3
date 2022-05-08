#include "Board.hpp"
#include <memory>
#include <cmath>
#include <utility>
#include <algorithm>
#include <iterator>
#include <random>
#include <iostream>

using std::uniform_int_distribution;
static std::random_device rd;
static std::mt19937 generator(rd());
static uniform_int_distribution<int> dist(1, 6);


Board::Board(uint8_t w, uint8_t h) :
    _w(w), _h(h),
    _tiles(new tile_t[w * h]),
    _state(new uint8_t[w * h])
{
    for(int i = 0; i < w*h; i++)
        _state[i] = STATE_BREAKING;
}

Board::Board(Board const& other) :
    _w(other._w), _h(other._h)
{
    auto size = other.size();

    _tiles = new tile_t[size];
    std::copy(other._tiles, other._tiles + size, _tiles);

    _state = new uint8_t[size];
    std::copy(other._state, other._state + size, _state);
}

void Board::operator =(Board const& other)
{
    _w = other._w;
    _h = other._h;
    auto size = other.size();

    _tiles = new tile_t[size];
    std::copy(other._tiles, other._tiles + size, _tiles);

    _state = new uint8_t[size];
    std::copy(other._state, other._state + size, _state);
}

Board::Board(Board&& other) :
    _w(other._w), _h(other._h)
{
    _tiles = other._tiles;
    other._tiles = nullptr;

    _state = other._state;
    other._state = nullptr;
}

Board::~Board()
{
    if(_tiles)
        delete[] _tiles;
    _tiles = nullptr;
    if(_state)
        delete[] _state;
    _state = nullptr;
}


tile_t* Board::operator () (uint8_t x, uint8_t y)
{
    if(x < _w && y < _h)
        return _tiles + y * _w + x;
    return nullptr;
}

void Board::select(tile_t* tile)
{
    if(nullptr == tile)
    {
        _selected = nullptr;
        return;
    }

    const auto state = *get_state(tile);
    if(STATE_NORMAL == state)
        _selected = tile;
}

void Board::move(tile_t* target)
{
    if(!_selected || !target)
        return;
    
    int pos1 = std::distance(_tiles, _selected);
    int pos2 = std::distance(_tiles, target);
    int x1 = pos1 % _w, y1 = pos1 / _w;
    int x2 = pos2 % _w, y2 = pos2 / _w;
    int dx = x2 - x1,   dy = y2 - y1;

    using std::abs;
    if(abs(dx) > abs(dy))
    {
        if(dx > 0 && x1 < _w - 1)
            swap(_selected + 1);
        if(dx < 0 && x1 > 0)
            swap(_selected - 1);
    }
    else if(abs(dx) < abs(dy))
    {
        if(dy > 0 && y1 < _h - 1)
            swap(_selected + _w);
        if(dy < 0 && y1 > 0)
            swap(_selected - _w);
    }
}

void Board::swap(tile_t* other)
{
    if(!other)
        std::cout << "Swapping nullptr." << std::endl;

    const auto state1 = *get_state(_selected);
    const auto state2 = *get_state(other);
    if(STATE_NORMAL == state1 && STATE_NORMAL == state2)
    {
        std::swap(*other, *_selected);
        auto pos1 = std::distance(_tiles, _selected);
        auto pos2 = std::distance(_tiles, other);
        auto x1 = pos1 % _w;
        auto y1 = pos1 / _w;
        auto x2 = pos2 % _w;
        auto y2 = pos2 / _w;

        bool match = false;
        for(int i = 2; i >= 0; i--)
        {
            match = check((*this)(x1 - i, y1)) || match;
            match = check((*this)(x1, y1 - i)) || match;
            match = check((*this)(x2 - i, y2)) || match;
            match = check((*this)(x2, y2 - i)) || match;
        }
    }
}

bool Board::check(tile_t* tile)
{
    if(tile == nullptr) return false;
    auto breaking = STATE_BREAKING + ANIMATION_MASK;

    auto state = get_state(tile);
    if(STATE_NORMAL != *state)
        return false;

    int pos = std::distance(_tiles, tile);
    int x = pos % _w;
    int y = pos / _w;

    if(x < _w - 2)
    {
        int same = 0;
        auto* other = tile;
        tile_t* row_end = _tiles + (y + 1) * _w;
        while(other < row_end)
        {
            if(*other != *tile)
                break;
            if(STATE_NORMAL != *get_state(other))
                break;
            same++;
            other++;
        }

        if(same > 2) 
            for(int i = 0; i < same; i++)
                *get_state(tile + i) = breaking;
    }

    if(y < _h - 2)
    {
        int same = 1;
        auto other = tile + _w;
        tile_t* col_end = _tiles + _h * _w + x;
        while(other < col_end)
        {
            if(*other != *tile)
                break;
            if(STATE_NORMAL != *get_state(other))
                break;
            same++;
            other += _w;
        }

        if(same > 2)
            for(int i = 0; i < same; i++)
                *get_state(tile + i * _w) = breaking;
    }

    return STATE_NORMAL != *state;
}

bool Board::check_all()
{
    bool result = false;
    for(size_t i = 0; i < size(); i++)
        result = check(_tiles + i) || result;
    return result;
}

uint8_t* Board::get_state(tile_t* tile)
{
    if(tile >= _tiles && tile < _tiles + size())
        return _state + std::distance(_tiles, tile);

    if(tile)
        std::cout << "Taking state of missptr."
                  << std::endl;
    else
        std::cout << "Taking state of nullptr."
                  << std::endl;

    return nullptr;
}

void Board::tick(uint8_t progress)
{
    bool new_tiles = false;

    auto tile = _tiles;
    auto end = _tiles + _w * _h;
    while(tile != end)
    {
        auto* state = get_state(tile);
        uint8_t animation = *state & ANIMATION_MASK;
        uint8_t animation_progress =
            std::min(progress, animation);

        if(animation)
            *state -= animation_progress;


        if(STATE_BREAKING == *state)
            fill(tile);

        if(STATE_FALLING == *state)
        {
            *state = STATE_NORMAL;
            new_tiles = true;
        }

        tile++;
    }

    if(new_tiles)
        check_all();
}

void Board::fill(tile_t* tile)
{
    auto* state = get_state(tile);
    int pos = std::distance(_tiles, tile);
    int y = pos / _w;

    if(y == 0)
    {
        *tile = dist(generator);
        *state = STATE_FALLING + ANIMATION_MASK;
        return;
    }

    auto* top = tile - _w;
    auto* top_state = get_state(top);
    if(STATE_NORMAL == *top_state)
    {
        *tile = *top;
        *top_state = STATE_BREAKING;
        *state = STATE_FALLING + ANIMATION_MASK;
    }

}
