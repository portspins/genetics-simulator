//---------------------------------------------------------------
// File: GeneticsSimController.cpp
// Purpose: Implementation file for the genetics simulation controller.
// Author: Matthew Hise
// Date: February 24, 2020
//---------------------------------------------------------------

#include "GeneticsSimController.h"
#include "ChromosomeFactory.h"
#include "GeneDescriptorFactory.h"
#include "OrganismFactory.h"
#include "Chromosome.h"
#include <time.h>

//-----------------------------------
// Get the singleton instance
//-----------------------------------
GeneticsSimController *GeneticsSimController::getInstance()
{
	static GeneticsSimController *theInstance = NULL;
	if (theInstance == NULL)
	{
		theInstance = new GeneticsSimController();
	}
	return theInstance;
}

//-----------------------------------
// Constructor
//-----------------------------------
GeneticsSimController::GeneticsSimController()
{
	// Initialize everything
	srand(time(NULL));
	offspring_count = 0;
	cross_count = 0;
	parent_one = parent_two = nullptr;
	view = new GeneticsSimView();
	string fileName = view->scanFileName();
	parser = GeneticsSimDataParser::getInstance();
	ChromosomeFactory *chFactory = ChromosomeFactory::getInstance();
	GeneDescriptorFactory *gdFactory = GeneDescriptorFactory::getInstance();
	OrganismFactory *oFactory = OrganismFactory::getInstance();
	Chromosome *newChromo = nullptr;
	parser->initDataFile(fileName);


	// Initialize some variables to hold data to construct gene descriptors and parents with
	char* a = new char;
	char* b = new char;
	*a = *b = ' ';
	string *trait = new string;
	string *dom = new string;
	string *rec = new string;
	string *strand_one = new string;
	string *strand_two = new string;
	double *crossover = new double;
	vector<Chromosome*> chromos;


	while (parser->getGeneData(trait, dom, a, rec, b, crossover)) {		// While there are still genes to be read
		addGeneDescriptor(gdFactory->buildGeneDescriptor(*trait, *a, *b, *dom, *rec, *crossover)); // Add them to the simulation
	}
	
	while (parser->getP1Chromosome(strand_one, strand_two)) {		             // While parent one still has chromosomes
		newChromo = chFactory->buildChromosome(*strand_one, *strand_two, gene_descriptors);		 // Construct new chromosome from strands
		if (newChromo != NULL) {
			chromos.push_back(newChromo);
		}
	}


	addParent(oFactory->buildOrganism(chromos));
	chromos.clear();  // Reset the vector of chromosomes


	while (parser->getP2Chromosome(strand_one, strand_two)) {		             // While parent one still has chromosomes
		newChromo = chFactory->buildChromosome(*strand_one, *strand_two, gene_descriptors);		 // Construct new chromosome from strands
		if (newChromo != NULL) {
			chromos.push_back(newChromo);
		}
	}

	addParent(oFactory->buildOrganism(chromos));

	delete a;
	delete b;
	delete trait;
	delete dom;
	delete rec;
	delete strand_one;
	delete strand_two;
	delete crossover;

}

//-----------------------------------
// Destructor
//-----------------------------------
GeneticsSimController::~GeneticsSimController()
{
	for (vector<GeneDescriptor*>::iterator itr = gene_descriptors.begin(); itr != gene_descriptors.end(); itr++) {
		delete *itr;
	}
	delete parent_one;
	delete parent_two;
	delete view;
	delete parser;
}

//-------------------------------------------------------------------------
// Get the number of offspring to generate, add them, and print the results
//-------------------------------------------------------------------------
void GeneticsSimController::generateOffspring()
{
	offspring_count = view->scanOffspringCount();		// Get the number of offspring
	cross_count = parent_one->crossWith(parent_two, offspring_count, gene_descriptors); // Generate those offspring
	view->printSimResults(parent_one, parser, cross_count);			// Print the results
	return;
}

//-----------------------------------
// Add a parent to the simulation
//-----------------------------------
void GeneticsSimController::addParent(Organism* parent)
{
	if (parent_one == nullptr) { // If there is not currently a parent
		parent_one = parent;	 // Add this as the first one
	}
	else {
		parent_two = parent;	// Otherwise add this as the second one
	}
	return;
}

//--------------------------------------------------------
// Tell the view to print the gene descriptors and parents
//--------------------------------------------------------
void GeneticsSimController::outputInitialModel()
{
	view->printGeneDescriptors(gene_descriptors);
	view->printParents(parent_one, parent_two, parser);
	return;
}

//----------------------------------------
// Add a gene descriptor to the simulation
//----------------------------------------
void GeneticsSimController::addGeneDescriptor(GeneDescriptor* gene_desc)
{
	gene_descriptors.push_back(gene_desc);
	return;
}
