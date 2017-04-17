#include "Neuron.h"

int Neuron::counter = 0;

int Neuron::getCounter() {
    return counter;
}

void Neuron::resetCounter() {
    Neuron::counter = 0;
}

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
    counter++;
    order_number = counter;
}

bool Neuron::operator==(const Neuron &rhs) const {
    return order_number == rhs.order_number &&
            layer_number == rhs.layer_number;
}

bool Neuron::operator!=(const Neuron &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Neuron &neuron) {
    os << "[No. " << neuron.order_number << " Layer " << neuron.layer_number << "]";
    return os;
}
