#include "Engine.hpp"
#include "GameData.hpp"
#include <iostream>
#include <chrono>
#include <queue>

#define TRACK_FRAMERATE false

void Engine::init_game_data()
{
    _data = new GameData(Board(8, 8));
}

void Engine::tick(float ms)
{
#if TRACK_FRAMERATE
    typedef std::chrono::steady_clock clock;
    typedef std::chrono::time_point<clock> time_p;
    using std::chrono::seconds;
    using std::chrono::duration_cast;

    static std::queue<time_p> frames;
    static auto begin = clock::now();


    auto last_frame = frames.front();
    frames.push(clock::now());

    while(frames.front() < frames.back() - seconds(1))
        frames.pop();

    if(duration_cast<seconds>(begin - last_frame)
        != duration_cast<seconds>(begin - frames.front()))
    {
        std::cout << "FPS: "
            << frames.size() << std::endl;
    }
#endif

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

