//
// Created by fajqa on 25.03.17.
//

#ifndef MACHINEGAMING_NEURON_H
#define MACHINEGAMING_NEURON_H


#include <vector>

class Neuron {
private:
    static int counter;
    int order_number;
    int layer_number;

public:
    Neuron(int layer_number);
    Neuron(const Neuron &neuron);

    int getOrderNumber() const;
    int getLayerNumber() const;

    bool operator==(const Neuron &rhs) const;

    bool operator!=(const Neuron &rhs) const;
};


#endif //MACHINEGAMING_NEURON_H
