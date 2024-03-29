#include "game/render.hpp"
#include "game/fonts.hpp"
#include "core/version.hpp"
#include "core/core.hpp"
#include <SDL2/SDL_render.h>
#include <iostream>

using std::cout;
using std::endl;


static auto& rnd = core::renderer;

namespace game
{
    struct VersionTag
    {
        SDL_Texture* texture;
        int width;
        int height;
    };

    static VersionTag get_version_tag();
}
using game::VersionTag;


void game::render_version_tag()
{
    static auto tag = get_version_tag();

    SDL_Rect dest {
        board_area.x + board_area.w - tag.width - 4,
        board_area.y + board_area.h - tag.height,
        tag.width,
        tag.height
    };

    SDL_RenderCopy(rnd, tag.texture, nullptr, &dest);
}


VersionTag game::get_version_tag()
{
    auto font = get_font(FT_DEBUG, 24);
    SDL_Color color {0, 0, 0, 255};

    string text;
    text += 'v' + std::to_string(VERSION_MAJOR);
    text += "." + std::to_string(VERSION_MINOR);

    auto surface = TTF_RenderUTF8_Blended
        (font, text.c_str(), color);

    if(!surface) {
        cout << "Failed rendering version tag." << endl;
        cout << TTF_GetError() << endl;
        return {
            nullptr,
            0, 0
        };
    }

    Point size { surface->w, surface->h };

    SDL_Texture* texture
        = SDL_CreateTextureFromSurface(rnd, surface);

    if(!surface) {
        cout << "Failed converting to texture." << endl;
        cout << SDL_GetError() << endl;
        return {
            nullptr,
            0, 0
        };
    }

    SDL_FreeSurface(surface);

    return {
        texture,
        size.x, size.y
    };
}

