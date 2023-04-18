#ifdef USE_SDL2_TTF
#include "utils/font_cache/internal.hpp"
#include <iostream>
#include <SDL2/SDL_timer.h>

using std::cout;
using std::endl;


FontCacheEntry* utils::find_font(FontCache* cache,
                                 fs::path path, int size)
{
    for(auto& entry : cache->entries) {
        if(entry.path == path)
            if(entry.size == size)
                return &entry;
    }

    return nullptr;
}

#endif // USE_SDL2_TTF
