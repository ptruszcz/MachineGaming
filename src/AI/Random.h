#ifndef MACHINEGAMING_RANDOM_H
#define MACHINEGAMING_RANDOM_H

#include <random>

class Random {
private:
    std::default_random_engine generator;

public:
    Random();

    int next(int min, int max);
    double next(double min, double max);
};

#endif //MACHINEGAMING_RANDOM_H
