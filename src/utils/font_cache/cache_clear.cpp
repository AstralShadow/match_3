#ifdef USE_SDL2_TTF
#include "utils/font_cache/internal.hpp"


void utils::cache_clear(FontCache* cache)
{
    while(cache->entries.size() > 0) {
        auto entry = cache->entries[0];
        cache->entries.pop_back();

        cache_destroy_entry(&entry);
    }
}

#endif // USE_SDL2_TTF
