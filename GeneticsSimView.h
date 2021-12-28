//---------------------------------------------------------------
// File: GeneticsSimView.h
// Purpose: Header file for the genetics simulation view.
// Author: Matthew Hise
// Date: February 24, 2020
//---------------------------------------------------------------

#pragma once
#include "Organism.h"
#include "GeneticsSimDataParser.h"
#include <cstdlib>
#include <string>

using namespace std;

class GeneticsSimView
{
public:
	GeneticsSimView(); // Default constructor
	~GeneticsSimView(); // Destructor
	void printParents(Organism* parent_one, Organism* parent_two, GeneticsSimDataParser* parser); // Print out the simulation's parents
	void printGeneDescriptors(vector<GeneDescriptor*> genes); // Print out the general gene data for the simulation
	void printOrganism(Organism* organism, GeneticsSimDataParser* parser); // Print out the data for one organism
	void printSimResults(Organism* parent, GeneticsSimDataParser* parser, int cross_count); // Compute the results of the simulation and show them
	int scanOffspringCount(); // Read in the number of offsrping from the user
	string scanFileName(); // Read in the name of the data file from the user
};

