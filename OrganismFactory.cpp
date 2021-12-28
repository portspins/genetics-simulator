//--------------------------------------------------------------
// File: OrganismFactory.cpp
// Purpose: Implementation file for a class to make organisms.
// Author: Matthew Hise
// Date: April 8, 2020
//-------------------------------------------------------------

#include "OrganismFactory.h"

OrganismFactory::OrganismFactory()
{
}

OrganismFactory::~OrganismFactory()
{
}

OrganismFactory *OrganismFactory::getInstance()
{
	static OrganismFactory *theInstance = NULL;
	if (theInstance == NULL)
	{
		theInstance = new OrganismFactory();
	}
	return theInstance;
}

Organism *OrganismFactory::buildOrganism(vector<Chromosome*> chromosomes)
{
	Organism *newOrganism = new Organism();
	for (vector<Chromosome*>::iterator itr = chromosomes.begin(); itr != chromosomes.end(); itr++) {
		newOrganism->addChromosome(*itr);
	}
	return newOrganism;
}
