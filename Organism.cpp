//---------------------------------------------------------------
// File: Organism.cpp
// Purpose: Implementation file for an organism class.
// Author: Matthew Hise
// Date: February 24, 2020
//---------------------------------------------------------------

#include "Organism.h"
#include "OrganismFactory.h"
#include "ChromosomeFactory.h"
#include <vector>
#include <cstdlib>

//-----------------------------------
// Default Constructor
//-----------------------------------
Organism::Organism()
{
}

//-----------------------------------
// Destructor
//-----------------------------------
Organism::~Organism()
{
	vector<Chromosome*>::iterator c_itr = chromosomes.begin();
	vector<Organism*>::iterator o_itr = offspring.begin();

	for (c_itr; c_itr != chromosomes.end(); c_itr++) {
		delete *c_itr;
	}

	for (o_itr; o_itr != offspring.end(); o_itr++) {
		delete *o_itr;
	}
}

Chromosome *Organism::getChromosome(unsigned int c_num)
{
	if (c_num >= 0 && c_num < chromosomes.size()) {
		return chromosomes.at(c_num);
	}
	return nullptr;
}


//--------------------------------------------------
// Perform the Mendelian cross between two organisms
//--------------------------------------------------
int Organism::crossWith(Organism* otherOrganism, int offspring_count, vector<GeneDescriptor*> descs)
{
	Organism* child = nullptr;
	OrganismFactory *oFactory = OrganismFactory::getInstance();
	ChromosomeFactory *chFactory = ChromosomeFactory::getInstance();
	vector<Chromosome*> chromos;
	Chromosome *chromo_one = nullptr;
	Chromosome *chromo_two = nullptr;
	Chromosome *chromo_final = nullptr;
	string strand_one;
	string strand_two;
	bool crossed = false;
	int cross_count = 0;
	int c_count = this->getChromosomeCount();

	for (int i = 0; i < offspring_count; i++) {
		for (int j = 0; j < c_count; j++) {
			chromo_one = this->getChromosome(j);
			chromo_two = otherOrganism->getChromosome(j);
			strand_one = chromo_one->getRandStrand();
			if (strand_one.length() > 1 && strand_one[strand_one.length() - 1] == '%') {
				strand_one = strand_one.substr(0, strand_one.length() - 1);
				if (!crossed) {
					cross_count++;
				}
				crossed = true;
			}
			if (strand_two.length() > 1 && strand_two[strand_two.length() - 1] == '%') {
				strand_two = strand_two.substr(0, strand_two.length() - 1);
				if (!crossed) {
					cross_count++;
				}
				crossed = true;
			}
			strand_two = chromo_two->getRandStrand();
			chromo_final = chFactory->buildChromosome(strand_one, strand_two, descs);
			chromos.push_back(chromo_final);
		}
		child = oFactory->buildOrganism(chromos);
		this->addChild(child);
		otherOrganism->addChild(child);
		chromos.clear();
		crossed = false;
	}

	return cross_count;
}

//-----------------------------------
// Get the organism's offspring count
//-----------------------------------
int Organism::getOffspringCount()
{
	return offspring.size();
}

//-----------------------------------
// Get the organism's offspring count
//-----------------------------------
int Organism::getChromosomeCount()
{
	return chromosomes.size();
}

//---------------------------------------
// Get a specific child from the organism
//---------------------------------------
Organism* Organism::getChild(int child)
{
	if (child < getOffspringCount()) // If it is a valid number of child
		return offspring.at(child); // Return that child
	return nullptr;
}

//----------------------------------
// Add a chromosome to the organism
//----------------------------------
void Organism::addChromosome(Chromosome *newChromo)
{
	chromosomes.push_back(newChromo);
}

//----------------------------
// Add a child to the organism
//----------------------------
void Organism::addChild(Organism* child) {
	offspring.push_back(child);
}