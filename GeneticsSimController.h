//---------------------------------------------------------------
// File: GeneticsSimController.h
// Purpose: Header file for the genetics simulation controller.
// Author: Matthew Hise
// Date: February 24, 2020
//---------------------------------------------------------------

#pragma once

#include "Organism.h"
#include "GeneticsSimView.h"
#include "GeneticsSimDataParser.h"

class GeneticsSimController
{
private:
	unsigned int offspring_count;		// The user's desired number of offspring
	int cross_count;					// The number of offspring that had a gene crossover
	Organism *parent_one;				// One of the parent organisms of the simulation
	Organism *parent_two;				// The other parent organism of the simulation
	GeneticsSimView *view;				// The view for the simulation
	GeneticsSimDataParser *parser;		// The parser to read the file and hold the general organism data
	vector<GeneDescriptor*> gene_descriptors;	// The gene descriptors read in from the data file

	GeneticsSimController(); // Private constructor
public:
	static GeneticsSimController *getInstance();	// Get the singleton instance
	~GeneticsSimController(); // Destructor
	void generateOffspring(); // Generate the desired number of offspring and print out the results
	void addParent(Organism* parent); // Add a parent to the simulation
	void outputInitialModel(); // Message the view to print out the general gene data and the parents
	void addGeneDescriptor(GeneDescriptor* gene_desc);
};

