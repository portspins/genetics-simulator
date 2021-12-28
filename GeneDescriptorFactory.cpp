//-------------------------------------------------------------------
// File: GeneDescriptorFactory.cpp
// Purpose: Implementation file for a class to make gene descriptors.
// Author: Matthew Hise
// Date: April 8, 2020
//-------------------------------------------------------------------

#include "GeneDescriptorFactory.h"

GeneDescriptorFactory::GeneDescriptorFactory()
{
}

GeneDescriptorFactory::~GeneDescriptorFactory()
{
}

GeneDescriptorFactory *GeneDescriptorFactory::getInstance()
{
	static GeneDescriptorFactory *theInstance = NULL;
	if (theInstance == NULL)
	{
		theInstance = new GeneDescriptorFactory();
	}
	return theInstance;
}

GeneDescriptor *GeneDescriptorFactory::buildGeneDescriptor(string desc, char d_allele, char r_allele, string d_pheno, string r_pheno, double chance)
{
	GeneDescriptor *newGeneDesc = new GeneDescriptor();
	// Initialize everything
	newGeneDesc->setDescription(desc);
	newGeneDesc->setDomAllele(d_allele);
	newGeneDesc->setRecAllele(r_allele);
	newGeneDesc->setDomPhenotype(d_pheno);
	newGeneDesc->setRecPhenotype(r_pheno);
	newGeneDesc->setCrossover(chance);
	return newGeneDesc;
}
