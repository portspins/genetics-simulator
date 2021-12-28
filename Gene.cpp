//---------------------------------------------------------------
// File: Gene.cpp
// Purpose: Implementation file for a class to store gene data.
// Author: Matthew Hise
// Date: February 24, 2020
//---------------------------------------------------------------

#include "Gene.h"
#include <string>

using namespace std;

//-----------------------------------
// Constructor
//-----------------------------------
Gene::Gene(char a, char b, GeneDescriptor* gene_desc) {
	setAlleleOne(a);				// Set strand one's allele
	setAlleleTwo(b);				// Set strand two's allele
	setGeneDesc(gene_desc);			// Attach the gene descriptor
}

//-----------------------------------
// Destructor
//-----------------------------------
Gene::~Gene() {
	delete gene_desc;
}

//-----------------------------------
// Set the first allele
//-----------------------------------
void Gene::setAlleleOne(char a) {
	strand_one_allele = a;
}

//-----------------------------------
// Set the second allele
//-----------------------------------
void Gene::setAlleleTwo(char b) {
	strand_two_allele = b;
}

//-----------------------------------
// Get the first allele
//-----------------------------------
char Gene::getAlleleOne() {
	return strand_one_allele;
}

//-----------------------------------
// Get the second allele
//-----------------------------------
char Gene::getAlleleTwo() {
	return strand_two_allele;
}

//-----------------------------------
// Get the first allele phenotype
//-----------------------------------
string Gene::getAlleleOnePheno() {
	if (gene_desc != NULL) {
		if (isupper(strand_one_allele)) {
			return gene_desc->getDomPhenotype();
		}
		return gene_desc->getRecPhenotype();
	}
	return "";
}

//-----------------------------------
// Get the second allele phenotype
//-----------------------------------
string Gene::getAlleleTwoPheno() {
	if (gene_desc != NULL) {
		if (isupper(strand_two_allele)) {
			return gene_desc->getDomPhenotype();
		}
		return gene_desc->getRecPhenotype();
	}
	return "";
}

//-----------------------------------
// Set the gene descriptor
//-----------------------------------
void Gene::setGeneDesc(GeneDescriptor* gene_desc) {
	this->gene_desc = gene_desc;
}

//-----------------------------------
// Get the trait name
//-----------------------------------
string Gene::getGeneStr() {
	if (gene_desc != NULL)		// As long as there is a gene descriptor set
		return gene_desc->getDescription();		// Get its description
	return "";			// Otherwise just return an empty string
}

//-----------------------------------
// Get the gene descriptor
//-----------------------------------
GeneDescriptor* Gene::getGeneDesc() {
	return gene_desc;
}