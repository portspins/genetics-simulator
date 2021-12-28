//---------------------------------------------------------------
// File: GeneDescriptor.h
// Purpose: Header file for a gene type class.
// Author: Matthew Hise
// Date: February 24, 2020
//---------------------------------------------------------------

#pragma once
#include <string>

using namespace std;

class GeneDescriptor
{
private:
	string desc; 					// The trait name
	char dominant_allele;			// This gene's dominant allele
	char recessive_allele;			// This gene's recessive allele
	string dominant_phenotype;   	// This gene's dominant physical description
	string recessive_phenotype;  	// This gene's recessive physical description
	double crossover;				// The chance of an allele crossing over from one strand to another
public:
	GeneDescriptor(); // Constructor
	~GeneDescriptor(); // Destructor
	string getDescription();
	void setDescription(string desc);
	void setDomAllele(char a);
	void setRecAllele(char a);
	char getDomAllele();
	char getRecAllele();
	void setDomPhenotype(string pheno);
	void setRecPhenotype(string pheno);
	string getDomPhenotype();
	string getRecPhenotype();
	void setCrossover(double chance);
	double getCrossover();
};

