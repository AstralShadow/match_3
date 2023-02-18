#include "random.hpp"
#include "types.hpp"
#include <random>
#include <memory>

// TODO dont recreate distributions for every call

using uniform_int = std::uniform_int_distribution<>;
using uniform_real = std::uniform_real_distribution<float>;
using geometric_int = std::geometric_distribution<>;

template<typename T>
static std::mt19937& generator(u32 seed = 0)
{
    static std::mt19937 _generator([seed](){
        if(seed != 0)
            return seed;
        return std::random_device()();
    }());

    return _generator;
}

const int cache_size = distribution_cache_size;


int random(int min, int max)
{
    struct CacheEntry
    {
        int min = 0;
        int max = 0;
        std::unique_ptr<uniform_int> dist = nullptr;
        u64 uses = 0;
    } static _cache[cache_size];

    // random(0, 0) can access undefined distribution
    if(min == max)
        return max;

    // Use cache
    for(u32 i = 0; i < cache_size; ++i) {
        auto& entry = _cache[i];
        if(entry.min == min && entry.max == max) {
            entry.uses++;
            int value = (*entry.dist)(generator<int*>());
            if(i > 0 && entry.uses > _cache[i - 1].uses)
                std::swap(_cache[i], _cache[i - 1]);
            return value;
        }
    }


    // Generate new entry in cache
    for(int i = 0; i < cache_size; ++i) {
        if(_cache[i].dist)
            continue;

        _cache[i].dist = std::make_unique<uniform_int>(min, max);
        _cache[i].min = min;
        _cache[i].max = max;
        _cache[i].uses = 1;
        return (*_cache[i].dist)(generator<int*>());
    }


    /* Replace last entry in cache */ {
        auto& last = _cache[cache_size - 1];
        last.dist = std::make_unique<uniform_int>(min, max);
        last.min = min;
        last.max = max;
        last.uses = 1;
        return (*last.dist)(generator<int*>());
    }
}


float randomf(float min, float max)
{
    struct CacheEntry
    {
        float min = 0;
        float max = 0;
        std::unique_ptr<uniform_real> dist = nullptr;
        u64 uses = 0;
    } static _cache[cache_size];

    // random(0, 0) can access undefined distribution
    if(min == max)
        return max;

    // Use cache
    for(u32 i = 0; i < cache_size; ++i) {
        auto& entry = _cache[i];
        if(entry.min == min && entry.max == max) {
            entry.uses++;
            float value = (*entry.dist)(generator<float*>());
            if(i > 0 && entry.uses > _cache[i - 1].uses)
                std::swap(_cache[i], _cache[i - 1]);
            return value;
        }
    }


    // Generate new entry in cache
    for(int i = 0; i < cache_size; ++i) {
        if(_cache[i].dist)
            continue;

        _cache[i].dist = std::make_unique<uniform_real>(min, max);
        _cache[i].min = min;
        _cache[i].max = max;
        _cache[i].uses = 1;
        return (*_cache[i].dist)(generator<float*>());
    }


    /* Replace last entry in cache */ {
        auto& last = _cache[cache_size - 1];
        last.dist = std::make_unique<uniform_real>(min, max);
        last.min = min;
        last.max = max;
        last.uses = 1;
        return (*last.dist)(generator<float*>());
    }
}


int geometric_random(float p)
{
    struct CacheEntry
    {
        float p = 0;
        std::unique_ptr<geometric_int> dist = nullptr;
        u64 uses = 0;
    } static _cache[cache_size];

    // Use cache
    for(u32 i = 0; i < cache_size; ++i) {
        auto& entry = _cache[i];
        if(entry.p == p) {
            entry.uses++;
            float value = (*entry.dist)(generator<int**>());
            if(i > 0 && entry.uses > _cache[i - 1].uses)
                std::swap(_cache[i], _cache[i - 1]);
            return value;
        }
    }


    // Generate new entry in cache
    for(int i = 0; i < cache_size; ++i) {
        if(_cache[i].dist)
            continue;

        _cache[i].dist = std::make_unique<geometric_int>(p);
        _cache[i].p = p;
        _cache[i].uses = 1;
        return (*_cache[i].dist)(generator<int**>());
    }


    /* Replace last entry in cache */ {
        auto& last = _cache[cache_size - 1];
        last.dist = std::make_unique<geometric_int>(p);
        last.p = p;
        last.uses = 1;
        return (*last.dist)(generator<int**>());
    }
}
/*

int geometric_random(float p) {
    static Cache<geometric_int> _cache;
    return _cache(p)(generator());

    return geometric_int(p)(generator());
}   
*/
