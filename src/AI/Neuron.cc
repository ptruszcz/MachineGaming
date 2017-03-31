//
// Created by fajqa on 25.03.17.
//

#include "Neuron.h"

int Neuron::neuron_counter = 0;

Neuron::Neuron() {}

int Neuron::getOrderNumber() const {
    return order_number;
}

int Neuron::getLayerNumber() const {
    return layer_number;
}

void Neuron::incrementLayerNumber() {
    ++layer_number;
}

Neuron::Neuron(int layer_number) : layer_number(layer_number) {
    neuron_counter++;
    order_number = neuron_counter;
}

bool Neuron::operator==(const Neuron &rhs) const {
    return order_number == rhs.order_number;
}

bool Neuron::operator!=(const Neuron &rhs) const {
    return !(rhs == *this);
}
