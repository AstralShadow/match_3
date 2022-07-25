#include "random.hpp"
#include <random>

using uniform_int = std::uniform_int_distribution<>;
using uniform_real = std::uniform_real_distribution<float>;
using geometric_int = std::geometric_distribution<>;

static std::random_device random_dev;
static std::mt19937 generator(random_dev());


int random(int min, int max) {
    return uniform_int(min, max)(generator);
}

float randomf(float min, float max) {
    return uniform_real(min, max)(generator);
}

int geometric_random(float p) {
    return geometric_int(p)(generator);
}   
