/*
File created by: Jakub Fajkowski
*/

#ifndef MACHINEGAMING_GENE_H
#define MACHINEGAMING_GENE_H

#include <cstddef>
#include <boost/shared_ptr.hpp>
#include "MutationType.h"

class Gene;
typedef std::shared_ptr<Gene> PGene;
typedef std::vector<PGene> Genes;

class Gene {
protected:
    size_t id;

public:
    Gene(size_t how_many);
    Gene(const Gene &gene);
    virtual PGene clone() const = 0;
    virtual void mutate(MutationType mutation_type) = 0;

    size_t getId() const;
};

#endif //MACHINEGAMING_GENE_H
