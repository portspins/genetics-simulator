//---------------------------------------------------------------
// File: Chromosome.h
// Purpose: Header file for a class to store chromosome data.
// Author: Matthew Hise
// Date: April 8, 2020
//---------------------------------------------------------------

#pragma once

#include "Gene.h"
#include <vector>
#include <string>

using namespace std;

class Chromosome
{
private:
	vector<Gene*> genes; // a list of the genes contained in the chromosome
public:
	Chromosome(); // constructor
	~Chromosome(); // destructor
	void addGene(Gene *newGene); // add a new gene to the chromosome
	Gene *getGene(unsigned int g_num);	// get the gene at a location
	int getGeneCount();  // returns the number of genes in the chromosome
	string getRandStrand(); // selects a random strand from the chromosome and uses the genes’ crossover chances to allow alleles from the other strand to be present in the returned strand for a child
};

