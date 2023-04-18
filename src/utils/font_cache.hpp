#ifndef INCLUDE_UTILS_FONT_CACHE_HPP
#define INCLUDE_UTILS_FONT_CACHE_HPP

#ifndef USE_SDL2_TTF
    #pragma message("Using utils/font_cache.hpp but USE_SDL2_TTF is not defined. Please add ' -D USE_SDL_TTF -lSDL2_ttf' to makefile")
#endif // USE_SDL2_TTF


#ifdef USE_SDL2_TTF

#include "utils/types.hpp"
#include <string>
#include <vector>
#include <filesystem>
#include <SDL2/SDL_ttf.h>

using std::string;
using std::vector;



namespace utils
{

    const bool print_font_cache_log = true;

    namespace fs = std::filesystem;

    struct FontCacheEntry {
        TTF_Font* font;
        fs::path path;
        int size;

        // Lower priority gets cleaned from cache first
        int priority;
        u32 last_use;
    };

    struct FontCache {
        vector<FontCacheEntry> entries;
        u32 max_cache_size = 20;
    };


    FontCache* create_cache();

    // Loads a font if not in cache, else uses cache.
    // Stores the font in cache.
    // May remove the least priority position that has not been used for longest.
    // If cache entry has lower priority than the one called with, increase it.
    TTF_Font* get_font(FontCache* cache, fs::path, int size, int priority = 0);

    // Decreases cache entry count to max_cache_size;
    void cache_trim(FontCache* cache);

    // Clears cache content
    // Frees up TTF_Font resources
    void cache_clear(FontCache* cache);

    // Call before discarding a cache pointer
    void destroy_cache(FontCache* cache);

}


#endif // USE_SDL2_TTF

#endif // INCLUDE_UTILS_FONT_CACHE_HPP
