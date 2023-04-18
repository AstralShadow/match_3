#ifdef USE_SDL2_TTF
#include "utils/font_cache/internal.hpp"
#include <iostream>
#include <SDL2/SDL_timer.h>

using std::cout;
using std::endl;


FontCacheEntry* utils::load_font(FontCache* cache,
                                 fs::path path, int size,
                                 int priority)
{
    FontCacheEntry entry {
        TTF_OpenFont(path.c_str(), size),
        path,
        size,
        priority,
        SDL_GetTicks()
    };

    if(!entry.font) {
        cout << "Error opening font!" << endl;
        cout << TTF_GetError() << endl;
        return nullptr;
    }

    if(cache->entries.size() >= cache->max_cache_size) {
        cache_trim(cache);
        cache_trim_one(cache);
    }

    cache->entries.push_back(entry);
    size_t pos = cache->entries.size() - 1;
    return &*(cache->entries.begin() + pos);
}

#endif // USE_SDL2_TTF
