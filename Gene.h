//---------------------------------------------------------------
// File: Gene.h
// Purpose: Header file for a class to store gene data.
// Author: Matthew Hise
// Date: February 24, 2020
//---------------------------------------------------------------

#pragma once

#include "GeneDescriptor.h"
#include <iostream>
#include <string>

using namespace std;

class Gene
{
private:
	char strand_one_allele;			// The allele in the first strand
	char strand_two_allele;			// The allele in the second strand
	GeneDescriptor *gene_desc;		// Pointer to the general gene details
public:
	Gene(char a, char b, GeneDescriptor* gene_desc); // Constructor
	~Gene(); // Destructor
	void setAlleleOne(char a);
	void setAlleleTwo(char a);
	char getAlleleOne();
	char getAlleleTwo();
	string getAlleleOnePheno();
	string getAlleleTwoPheno();
	void setGeneDesc(GeneDescriptor* gene_desc);
	GeneDescriptor* getGeneDesc();
	string getGeneStr(); // Get the gene's trait name
};

