//
// Created by fajqa on 18.04.17.
//

#ifndef MACHINEGAMING_COUNTER_HPP
#define MACHINEGAMING_COUNTER_HPP

#include <cstddef>

template<typename T>
class Counter {
public:
    Counter() { ++count; }

    static std::size_t howMany() { return count; }
    static void resetCounter();

private:
    static std::size_t count;
};

template <typename T>
std::size_t Counter<T>::count = 0;

template <typename T>
void Counter<T>::resetCounter() {
    count = 0;
}

#endif //MACHINEGAMING_COUNTER_HPP