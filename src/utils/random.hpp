#ifndef INCLUDE_UTILS_RANDOM_HPP
#define INCLUDE_UTILS_RANDOM_HPP

// WARNING: using random.hpp is deprecated. Use trandom.hpp instead.


int random(int first, int second);
float randomf(float first, float second);

// https://en.cppreference.com/w/cpp/numeric/random/geometric_distribution
int geometric_random(float p);


// These functions cache the most used distributions.
// Prefer calls to templates in trandom.hpp.

const int distribution_cache_size = 30;
const bool call_warning = true;

#endif // INCLUDE_UTILS_RANDOM_HPP
