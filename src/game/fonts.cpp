#include "game/fonts.hpp"
#include "utils/font_cache.hpp"

namespace fs = std::filesystem;


TTF_Font* game::get_font(FontTarget target, int size)
{
    static auto* cache = utils::create_font_cache();

    fs::path file;

    switch(target) {
        case FT_DEBUG:
            file = "LiberationSerif-Regular.ttf";
            break; 
        case FT_DEFAULT:
            file = "comic_shanns_2.ttf";
            break;
    }

    fs::path path = "assets/fonts" / file;

    return utils::get_font(cache, path, size);
}

