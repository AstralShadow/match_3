#include "Engine.hpp"
#include "GameData.hpp"
#include <iostream>
#include <chrono>
#include <queue>

void Engine::init_game_data()
{
    _data = new GameData({8, 8});
}

void Engine::tick(uint32_t)
{
    typedef std::chrono::steady_clock clock;
    typedef std::chrono::time_point<clock> time_p;
    using std::chrono::seconds;
    static std::queue<time_p> frames;

    frames.push(clock::now());
    while(frames.front() < frames.back() - seconds(1))
        frames.pop();

    //std::cout << "FPS: " << frames.size() << std::endl;

    _data->board.tick(1);
}

