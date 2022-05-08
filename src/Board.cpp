#include "Board.hpp"
#include <memory>
#include <cmath>
#include <utility>


Board::Board(uint8_t w, uint8_t h) :
    _w(w), _h(h), _tiles(new tile_t[w * h])
{ }

Board::~Board()
{
    if(_tiles)
        delete[] _tiles;
    _tiles = nullptr;
}

Board::Board(Board const& other) :
    _w(other._w), _h(other._h)
{
    auto size = other.size();
    auto first = other._tiles;
    auto last = other._tiles + size;

    _tiles = new tile_t[size];
    std::copy(first, last, _tiles);
}

Board::Board(Board&& other) :
    _w(other._w), _h(other._h)
{
    _tiles = other._tiles;
    other._tiles = nullptr;
}


tile_t* Board::operator () (uint8_t x, uint8_t y)
{
    if(x < _w && y < _h)
        return _tiles + y * _w + x;
    return nullptr;
}

void Board::move(tile_t* target)
{
    if(!_selected || !target)
        return;
    
    int pos1 = _selected - _tiles;
    int pos2 = target - _tiles;
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
    std::swap(*other, *_selected);
}

