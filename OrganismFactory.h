//---------------------------------------------------------------
// File: OrganismFactory.h
// Purpose: Header file for a class to create Organisms.
// Author: Matthew Hise
// Date: April 8, 2020
//-------------------------------------------------------------

#pragma once

#include "Organism.h"

using namespace std;

class OrganismFactory
{
private:
	OrganismFactory();			        // Private Constructor

public:
	~OrganismFactory();				// Destructor
	static OrganismFactory *getInstance();	// Get the singleton instance
	Organism *buildOrganism(vector<Chromosome*> chromosomes);
};

