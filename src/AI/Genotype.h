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

    static size_t makeEqualSize(Genotype &parent_a, Genotype &parent_b);
    static Genotype createChild(Genotype &parent_a, Genotype &parent_b);
    static PGene getRandomGene(PGene gene_a, PGene gene_b);
    
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
