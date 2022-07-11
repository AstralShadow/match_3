#include "Board.hpp"
#include <memory>
#include <iterator>
#include <iostream>

Board::Board(uint8_t w, uint8_t h) :
    _w(w), _h(h),
    _tiles(new tile_t[w * h]),
    _state(new uint8_t[w * h])
{
    for(int i = 0; i < w*h; i++)
        _state[i] = STATE_BREAKING;
    _focused = _tiles;
}

Board::Board(Board const& other) :
    _w(other._w), _h(other._h)
{
    auto size = other.size();

    _tiles = new tile_t[size];
    std::copy(other._tiles, other._tiles + size, _tiles);

    _state = new uint8_t[size];
    std::copy(other._state, other._state + size, _state);

    _focused = _tiles;
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

    _focused = _tiles;
}

Board::Board(Board&& other) :
    _w(other._w), _h(other._h)
{
    _tiles = other._tiles;
    other._tiles = nullptr;

    _state = other._state;
    other._state = nullptr;

    _focused = other._focused;
    _selected = other._selected;
    other._focused = nullptr;
    other._selected= nullptr;
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

