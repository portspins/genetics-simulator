//---------------------------------------------------------------
// File: ChromosomeFactory.h
// Purpose: Header file for a class to create Chromosomes.
// Author: Matthew Hise
// Date: April 8, 2020
//-------------------------------------------------------------

#pragma once

#include "Chromosome.h"

class ChromosomeFactory
{
private:
	ChromosomeFactory();			        // Private Constructor

public:
	~ChromosomeFactory();				// Destructor
	static ChromosomeFactory *getInstance();	// Get the singleton instance
	Chromosome* buildChromosome(string strand_one, string strand_two, vector<GeneDescriptor*> gene_descs);
};

