//
// Created by fajqa on 25.03.17.
//

#ifndef MACHINEGAMING_NEURON_H
#define MACHINEGAMING_NEURON_H


#include <vector>
#include <boost/shared_ptr.hpp>
#include <ostream>

class Neuron;
typedef std::shared_ptr<Neuron> PNeuron;

class Neuron {
private:
    static int counter;
    int order_number;
    int layer_number;

public:
    Neuron(int layer_number);

    static int getCounter();
    static void resetCounter();
    int getOrderNumber() const;
    int getLayerNumber() const;
    void incrementLayerNumber();

    bool operator==(const Neuron &rhs) const;
    bool operator!=(const Neuron &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Neuron &neuron);
};


#endif //MACHINEGAMING_NEURON_H
