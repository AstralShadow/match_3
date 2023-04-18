#ifdef USE_SDL2_TTF
#include "utils/font_cache/internal.hpp"


void utils::cache_trim(FontCache* cache)
{
    const auto max = cache->max_cache_size;
    while(cache->entries.size() > max)
        cache_trim_one(cache);
}

#endif // USE_SDL2_TTF
