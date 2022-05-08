#include "Engine.hpp"
#include "GameData.hpp"
#include <random>
#include <iostream>

using std::uniform_int_distribution;
static std::random_device rd;
static std::mt19937 generator(rd());


void Engine::init_game_data()
{
    _data = new GameData({10, 10});

    uniform_int_distribution<int> dist(0, 7);
    auto& board = _data->board;

    for(int y = 0; y < board.h(); y++)
    {
        for(int x = 0; x < board.w(); x++)
        {
            auto* tile = board(x, y);
            *tile = dist(generator);
            std::cout << (int) *tile << ' ';
        }
        std::cout << std::endl;
    }
}

void Engine::tick(uint32_t ticks)
{
    
}

