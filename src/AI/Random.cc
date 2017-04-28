#include "Random.h"

Random::Random() {}

int Random::next(int min, int max) {
    if (min == max)
        return min;
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

double Random::next(double min, double max) {
    if (min == max)
        return min;
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}
