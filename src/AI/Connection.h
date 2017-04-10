//
// Created by fajqa on 25.03.17.
//

#ifndef MACHINEGAMING_CONNECTION_H
#define MACHINEGAMING_CONNECTION_H

#include <boost/shared_ptr.hpp>
#include <ostream>
#include "Neuron.h"

class Connection {
private:
    static int counter;
    static double weight_variance;

    int order_number;
    PNeuron input;
    PNeuron output;
    double weight;

public:

    Connection() {}
    bool enabled;

    Connection(const PNeuron &input, const PNeuron &output);

    void randomizeWeight();

    static int getCounter();
    static void resetCounter();
    static double getWeightVariance();
    static void setWeightVariance(double weight_variance);
    int getOrderNumber() const;
    const PNeuron &getInput() const;
    const PNeuron &getOutput() const;
    bool isEnabled() const;
    double getWeight() const;

    bool operator==(const Connection &rhs) const;
    bool operator!=(const Connection &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const Connection &connection);
};


#endif //MACHINEGAMING_CONNECTION_H
