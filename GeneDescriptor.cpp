//---------------------------------------------------------------
// File: GeneDescriptor.cpp
// Purpose: Implementation file for a gene type class.
// Author: Matthew Hise
// Date: February 24, 2020
//---------------------------------------------------------------

#include "GeneDescriptor.h"

//-----------------------------------
// Constructor
//-----------------------------------
GeneDescriptor::GeneDescriptor()
{
}

//-----------------------------------
// Destructor
//-----------------------------------
GeneDescriptor::~GeneDescriptor()
{
}

//-----------------------------------
// Get the trait description
//-----------------------------------
string GeneDescriptor::getDescription()
{
	return desc;
}

//-----------------------------------
// Set the trait description
//-----------------------------------
void GeneDescriptor::setDescription(string desc)
{
	this->desc = desc;
	return;
}

//-----------------------------------
// Set the dominant allele
//-----------------------------------
void GeneDescriptor::setDomAllele(char a)
{
	dominant_allele = a;
	return;
}

//-----------------------------------
// Set the recessive allele
//-----------------------------------
void GeneDescriptor::setRecAllele(char a)
{
	recessive_allele = a;
	return;
}

//-----------------------------------
// Get the dominant allele
//-----------------------------------
char GeneDescriptor::getDomAllele()
{
	return dominant_allele;
}

//-----------------------------------
// Get the recessive allele
//-----------------------------------
char GeneDescriptor::getRecAllele()
{
	return recessive_allele;
}

//-----------------------------------
// Set the dominant phenotype
//-----------------------------------
void GeneDescriptor::setDomPhenotype(string pheno)
{
	dominant_phenotype = pheno;
	return;
}

//-----------------------------------
// Set the recessive phenotype
//-----------------------------------
void GeneDescriptor::setRecPhenotype(string pheno)
{
	recessive_phenotype = pheno;
	return;
}

//-----------------------------------
// Get the dominant phenotype
//-----------------------------------
string GeneDescriptor::getDomPhenotype()
{
	return dominant_phenotype;
}

//-----------------------------------
// Get the recessive phenotype
//-----------------------------------
string GeneDescriptor::getRecPhenotype()
{
	return recessive_phenotype;
}

void GeneDescriptor::setCrossover(double chance)
{
	crossover = chance;
}

double GeneDescriptor::getCrossover()
{
	return crossover;
}
