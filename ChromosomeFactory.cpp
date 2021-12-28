//---------------------------------------------------------------
// File: ChromosomeFactory.cpp
// Purpose: Implementation file for a class to make chromosomes.
// Author: Matthew Hise
// Date: April 8, 2020
//---------------------------------------------------------------

#include "ChromosomeFactory.h"
#include <sstream>

ChromosomeFactory::ChromosomeFactory()
{
}

ChromosomeFactory::~ChromosomeFactory()
{
}

ChromosomeFactory *ChromosomeFactory::getInstance()
{
	static ChromosomeFactory *theInstance = NULL;
	if (theInstance == NULL)
	{
		theInstance = new ChromosomeFactory();
	}
	return theInstance;
}

Chromosome *ChromosomeFactory::buildChromosome(string strand_one, string strand_two, vector<GeneDescriptor*> gene_descs)
{
	Chromosome *newChromo = new Chromosome();
	GeneDescriptor *desc = nullptr;
	Gene* newGene = nullptr;
	string token_a;
	string token_b;
	istringstream stream_a(strand_one);
	istringstream stream_b(strand_two);

	while (getline(stream_a, token_a, ' ')) {

		if (token_a[0] == '%') { return newChromo; }

		if (getline(stream_b, token_b, ' ') && tolower(token_a[0]) == tolower(token_b[0])) {
			// Find the gene descriptor for this gene
			for (vector<GeneDescriptor*>::iterator itr = gene_descs.begin(); itr != gene_descs.end(); itr++) {
				if ((*itr)->getRecAllele() == tolower(token_b[0])) {
					desc = *itr;
					break;
				}
			}
			newGene = new Gene(token_a[0], token_b[0], desc);
			newChromo->addGene(newGene);
		}
		else {
			cout << "Error! Strands do not match." << endl;
			system("pause");
			delete newChromo;
			return nullptr;
		}
	}
	
	return newChromo;
}
