//---------------------------------------------------------------
// File: Organism.h
// Purpose: Header file for an organism class.
// Author: Matthew Hise
// Date: February 24, 2020
//---------------------------------------------------------------

#pragma once
#include <cstring>
#include <vector>
#include <iostream>
#include "Chromosome.h"
#include "Organism.h"
#include "GeneDescriptor.h"

using namespace std;

class Organism
{
private:
	vector<Chromosome*> chromosomes;  // All the chromosomes defining the organism
	vector<Organism*> offspring;	  // This organism's offspring
public:
	Organism();
	~Organism(); // Destructor
	Chromosome *getChromosome(unsigned int c_num);
	//void updateGeneCounts(vector<vector<int*>> counts); // Update the counts of each genotype for each gene in an organism
	int crossWith(Organism * otherOrganism, int offspring_count, vector<GeneDescriptor*> descs);
	// Performs the Mendelian cross between two organisms of the same type
	int getOffspringCount();
	int getChromosomeCount();
	void addChild(Organism* child);
	Organism* getChild(int child);
	void addChromosome(Chromosome* newChromo);
};