#include "Engine.hpp"
#include "GameData.hpp"
#include <iostream>
#include <chrono>
#include <queue>

void Engine::init_game_data()
{
    _data = new GameData({8, 8});
}

void Engine::tick(float ms)
{
    typedef std::chrono::steady_clock clock;
    typedef std::chrono::time_point<clock> time_p;
    using std::chrono::seconds;
    static std::queue<time_p> frames;

    frames.push(clock::now());
    while(frames.front() < frames.back() - seconds(1))
        frames.pop();

    //std::cout << "FPS: " << frames.size() << std::endl;


    static float progress = 0;
    progress += ms;
    constexpr float board_step =
        1000.0f / TARGET_BOARD_TICKRATE;

    while(progress > board_step)
    {
        progress -= board_step;
        _data->board.tick(1);
    }
}

