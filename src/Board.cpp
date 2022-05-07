#include "Board.hpp"

Board::Board(uint8_t w, uint8_t h) :
    _w(w), _h(h), _tiles(new tile_t[w * h])
{ }

Board::~Board()
{
    if(_tiles)
        delete[] _tiles;
    _tiles = nullptr;
}


tile_t* Board::operator () (uint8_t x, uint8_t y)
{
    if(x < _w && y < _h)
        return _tiles + y * _w + x;
    return nullptr;
}
