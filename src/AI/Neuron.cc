//
// Created by fajqa on 25.03.17.
//

#include "Neuron.h"

int Neuron::getOrderNumber() const {
    return order_number;
}

int Neuron::getLayerNumber() const {
    return layer_number;
}

Neuron::Neuron(int layer_number) : layer_number(layer_number) {
    counter++;
    order_number = counter;
}

Neuron::Neuron(const Neuron &neuron) {
    order_number = neuron.order_number;
    layer_number = neuron.layer_number;
}
