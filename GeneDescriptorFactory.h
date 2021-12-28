//---------------------------------------------------------------
// File: GeneDescriptorFactory.h
// Purpose: Header file for a class to create Gene Descriptors.
// Author: Matthew Hise
// Date: April 8, 2020
//-------------------------------------------------------------

#pragma once

#include "GeneDescriptor.h"

class GeneDescriptorFactory
{
private:
	GeneDescriptorFactory();			        // Private Constructor

public:
	~GeneDescriptorFactory();				// Destructor
	static GeneDescriptorFactory *getInstance();	// Get the singleton instance
	GeneDescriptor* buildGeneDescriptor(string desc, char d_allele, char r_allele, string d_pheno, string r_pheno, double chance);
};

