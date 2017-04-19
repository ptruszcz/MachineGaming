#ifndef MACHINEGAMING_GENOTYPE_H
#define MACHINEGAMING_GENOTYPE_H

#include "Gene.h"
#include "Random.h"

class Genotype;
typedef std::shared_ptr<Genotype> PGenotype;

class Genotype {
private:
    static Random random;
    Genes genes;
    
public:
    static Genotype crossover(Genotype &parent_a, Genotype &parent_b);

    void insert(const PGene &gene);
    void erase(const PGene &gene);
    Genes getGenes();

    PGene & operator[](size_t index);
    const PGene & operator[](size_t index) const;
    bool operator==(const Genotype &rhs) const;
    bool operator!=(const Genotype &rhs) const;
};


#endif //MACHINEGAMING_GENOTYPE_H
