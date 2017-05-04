/*
File created by: Jakub Fajkowski
*/

#ifndef MACHINEGAMING_GENOTYPE_H
#define MACHINEGAMING_GENOTYPE_H

#include <ostream>
#include "Gene.h"
#include "Random.h"

class Genotype;
typedef std::shared_ptr<Genotype> PGenotype;

class Genotype {
private:
    static Random random;
    Genes genes;

    static PGenotype createChild(Genotype &parent_a, Genotype &parent_b);
    static size_t makeEqualSize(Genotype &parent_a, Genotype &parent_b);
    static PGene chooseGene(const PGene &gene_a, const PGene &gene_b);
    static PGene getRandomGene(const PGene &gene_a, const PGene &gene_b);
    
public:
    Genotype() {};
    Genotype(const Genotype &genotype);
    PGenotype clone() const;

    static PGenotype crossover(Genotype &parent_a, Genotype &parent_b);

    void insert(const PGene &gene);
    void erase(const PGene &gene);

    PGene & operator[](size_t index);
    const PGene & operator[](size_t index) const;
    bool operator==(const Genotype &rhs) const;
    bool operator!=(const Genotype &rhs) const;
    friend std::ostream &operator<<(std::ostream &os, const Genotype &genotype);

    Genes getGenes() const;
};


#endif //MACHINEGAMING_GENOTYPE_H
