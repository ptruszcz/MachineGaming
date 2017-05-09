#include "Random.h"

Random::Random() {}

double Random::next() {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator_);
}

int Random::next(int min, int max) {
    if (min == max)
        return min;
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator_);
}

double Random::next(double min, double max) {
    if (min == max)
        return min;
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator_);
}
