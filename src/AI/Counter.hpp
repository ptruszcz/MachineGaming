/*
File created by: Jakub Fajkowski
*/

#ifndef MACHINEGAMING_COUNTER_HPP
#define MACHINEGAMING_COUNTER_HPP

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

template<typename T>
class Counter {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & count;
    }

    static size_t count;

public:
    Counter() { ++count; }
    Counter(const Counter &) {}
    ~Counter() {}

    static void resetCounter();

    static size_t getCount();
    static void setCount(size_t count);
};

template <typename T>
size_t Counter<T>::count = 0;

template <typename T>
void Counter<T>::resetCounter() {
    count = 0;
}

template <typename T>
size_t Counter<T>::getCount() {
    return count;
}

template <typename T>
void Counter<T>::setCount(size_t count) {
    Counter<T>::count = count;
}

#endif //MACHINEGAMING_COUNTER_HPP
