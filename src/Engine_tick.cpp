#include "Engine.hpp"
#include "GameData.hpp"
#include <random>

using std::uniform_int_distribution;
static std::random_device rd;
static std::mt19937 generator(rd());


void Engine::init_game_data()
{
    _data = new GameData {
        Board {10, 10}
    };

    uniform_int_distribution<int> dist(0, 7);
    auto& board = _data->board;
    for(int x = 0; x < board.w(); x++)
    for(int y = 0; y < board.h(); y++)
    {
        auto* tile = board(x, y);
        *tile = dist(generator);
    }
}

void Engine::tick(uint32_t ticks)
{

}
