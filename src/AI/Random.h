/*
File created by: Jakub Fajkowski
*/

#ifndef MACHINEGAMING_RANDOM_H
#define MACHINEGAMING_RANDOM_H

#include <random>

class Random {
private:
    std::default_random_engine generator_;

public:
    Random();

    double next();
    int next(int min, int max);
    double next(double min, double max);
};

#endif //MACHINEGAMING_RANDOM_H
