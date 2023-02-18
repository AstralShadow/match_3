#ifndef INCLUDE_UTILS_TRANDOM_HPP
#define INCLUDE_UTILS_TRANDOM_HPP

#include <random>

// Creates different static mt19937 and distribution
//  for every combination of template arguments.
// Use undeclared struct pointers for T for variety.

// Set seed on first call. Default is 0 for random seed.


// Returns a value in range [a, b]
template<int a, int b, typename T = int>
inline int random(int seed = 0);

// Returns a value in range [0, 1)
template<typename T = int>
inline int randomf(int seed = 0);



template<int a, int b, typename T>
inline std::mt19937& generator(int seed = 0)
{
    static std::mt19937 _generator([seed](){
        if(seed != 0)
            return seed;
        return std::random_device()();
    }());

    return _generator;
}


template<int a, int b, typename T>
inline int random(int seed)
{
    static std::uniform_int_distribution<>
        dist(a, b);

    return dist(generator<a, b, T>(seed));
}


template<typename T>
inline int randomf(int seed)
{
    static std::uniform_real_distribution<float>
        dist(0, 1);

    return dist(generator<0, 0, T*>(seed));
}


#endif // INCLUDE_UTILS_TRANDOM_HPP
