//---------------------------------------------------------------
// File: Chromosome.cpp
// Purpose: Implementation file for a class to store chromosomes.
// Author: Matthew Hise
// Date: April 8, 2020
//---------------------------------------------------------------

#include "Chromosome.h"
#include <time.h>
#include <cstdlib>

Chromosome::Chromosome()
{
}

Chromosome::~Chromosome()
{
}

void Chromosome::addGene(Gene *newGene)
{
	genes.push_back(newGene);
}

Gene *Chromosome::getGene(unsigned int g_num)
{
	if (g_num >= 0 && g_num < genes.size()) {
		return genes.at(g_num);
	}
	return nullptr;
}

int Chromosome::getGeneCount() {
	return genes.size();
}

string Chromosome::getRandStrand()
{
	int s = rand() % 2;
	int c = 0;
	string strand = "";
	Gene *this_gene;
	GeneDescriptor *gene_desc;
	bool crossed = false;

	for (unsigned int i = 0; i < genes.size(); i++) {
		this_gene = getGene(i);
		if (this_gene != NULL) {
			c = rand() % 100;

			gene_desc = this_gene->getGeneDesc();
			if (c < gene_desc->getCrossover()) {
				s = abs(s - 1);
				crossed = true;
			}

			if (s == 0) {
				strand += this_gene->getAlleleOne();
			}
			else {
				strand += this_gene->getAlleleTwo();
			}

			strand += ' ';

		}
	}

	if (strand.length() > 1) {
		strand = strand.substr(0, strand.length() - 1);  // Trim whitespace off the end
	}

	if (crossed) {
		strand += "%";  // Mark the strand as having had a cross
	}

	return strand;
}
