//
// Created by fajqa on 25.03.17.
//

#ifndef MACHINEGAMING_NEURON_H
#define MACHINEGAMING_NEURON_H


#include <vector>

class Neuron {
private:
    static int neuron_counter;
    int order_number;
    int layer_number;

    Neuron();

public:
    Neuron(int layer_number);

    int getOrderNumber() const;
    int getLayerNumber() const;
    void incrementLayerNumber();

    bool operator==(const Neuron &rhs) const;

    bool operator!=(const Neuron &rhs) const;
};


#endif //MACHINEGAMING_NEURON_H
