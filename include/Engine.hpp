#ifndef INCLUDE_ENGINE_HPP
#define INCLUDE_ENGINE_HPP

#include <cstdint>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_MouseButtonEvent;
struct GameData;
typedef uint8_t tile_t;

const char* const TITLE = "Match 3";
const int WIDTH = 800;
const int HEIGHT = 600;


class Engine
{
public:
    Engine();
    ~Engine();

    void run();

private:
    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;

    bool _running = false;
    GameData* _data = nullptr;


    void create_window();
    void create_renderer();
    void init_game_data();

    void poll_events();
    void process(SDL_MouseButtonEvent&);
    void tick(uint32_t ticks);
    void render();

    tile_t* get_tile_at(int x, int y);
};

#endif // INCLUDE_ENGINE_HPP
