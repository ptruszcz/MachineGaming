/**
 * @class Connection
 * @brief Represents connection between neurons.
 * @details It provides Gene methods. It is stored in Genotype
 * and when needed Phenome connection matrices are built using it.
 * @author Jakub Fajkowski
 */

#ifndef MACHINEGAMING_CONNECTION_H
#define MACHINEGAMING_CONNECTION_H

#include <boost/serialization/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <ostream>

#include "Counter.hpp"
#include "Gene.h"
#include "Random.h"
#include "Neuron.h"

class Connection;
typedef std::shared_ptr<Connection> PConnection;
typedef std::vector<PConnection> Connections;

class Connection : public Counter<Connection>, public Gene {
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Counter<Connection>>(*this);
        ar & boost::serialization::base_object<Gene>(*this);
        ar & input_;
        ar & output_;
        ar & weight_;
    }

    static Random random;

    PNeuron input_;
    PNeuron output_;
    double weight_;
    
    void randomizeWeight();
public:
    static double weight_variance;

    Connection();
    Connection(const PNeuron &input, const PNeuron &output);
    Connection(const Connection &connection);
    
    virtual PGene clone() const;
    virtual void mutate(MutationType mutation_type);

    bool operator==(const Connection &rhs) const;
    bool operator!=(const Connection &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Connection &connection);

    const PNeuron &getInput() const;
    const PNeuron &getOutput() const;
    double getWeight() const;
};


#endif //MACHINEGAMING_CONNECTION_H
