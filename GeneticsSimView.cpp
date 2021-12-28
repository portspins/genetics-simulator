//---------------------------------------------------------------
// File: GeneticsSimView.cpp
// Purpose: Implementation file for the genetics simulation view.
// Author: Matthew Hise
// Date: February 24, 2020
//---------------------------------------------------------------

#include "GeneticsSimView.h"

//-----------------------------------
// Constructor
//-----------------------------------
GeneticsSimView::GeneticsSimView()
{
}

//-----------------------------------
// Destructor
//-----------------------------------
GeneticsSimView::~GeneticsSimView()
{
}

//-----------------------------------
// Print the parents
//-----------------------------------
void GeneticsSimView::printParents(Organism* parent_one, Organism* parent_two, GeneticsSimDataParser* parser)
{
	// Print parent one
	cout << "Sim parent 1" << endl;
	printOrganism(parent_one, parser);
	// Print parent two
	cout << endl << "Sim parent 2" << endl;
	printOrganism(parent_two, parser);
	cout << endl;
	return;
}

//-----------------------------------
// Print the gene descriptors
//-----------------------------------
void GeneticsSimView::printGeneDescriptors(vector<GeneDescriptor*> genes)
{
	cout << "Master Genes:" << endl;
	for (vector<GeneDescriptor*>::iterator itr = genes.begin(); itr != genes.end(); itr++) {	// For each gene descriptor, print its data
		cout << "\tTrait Name: " << (*itr)->getDescription() << endl;
		cout << "\t\tDominant Name: " << (*itr)->getDomPhenotype() << "(" << (*itr)->getDomAllele() << ")" << endl;
		cout << "\t\tRecessive Name: " << (*itr)->getRecPhenotype() << "(" << (*itr)->getRecAllele() << ")" << endl;
		cout << "\t\tCrossover Chance: " << (*itr)->getCrossover() << endl;
	}
	cout << endl;
	return;
}

//-----------------------------------
// Print an organism
//-----------------------------------
void GeneticsSimView::printOrganism(Organism* organism, GeneticsSimDataParser* parser)
{
	Chromosome *chromo = nullptr;
	Gene *gene = nullptr;
	cout << "\tScientific Name: " << parser->getCommonName() << endl;
	cout << "\tChromosomes:" << endl;
	for (int i = 0; i < organism->getChromosomeCount(); i++) {	// Print each of the chromosomes in the organism
		chromo = organism->getChromosome(i);
		if (chromo != nullptr) {
			cout << "\t\tChromosome " << (i + 1) << endl;
			for (int j = 0; j < chromo->getGeneCount(); j++) {
				gene = chromo->getGene(j);
				if (gene != nullptr) {
					cout << "\t\t\tGene Type: " << gene->getGeneStr() << endl;
					cout << "\t\t\t\tAllele 1: " << gene->getAlleleOnePheno() << " (" << gene->getAlleleOne() << ")" << endl;
					cout << "\t\t\t\tAllele 2: " << gene->getAlleleTwoPheno() << " (" << gene->getAlleleTwo() << ")" << endl;
				}
			}
			cout << endl;
		}
	}
	return;
}

//------------------------------------
// Print the results of the simulation
//------------------------------------
void GeneticsSimView::printSimResults(Organism* parent, GeneticsSimDataParser* parser, int cross_count)
{
	int count = parent->getOffspringCount();	// Get the number of offspring the parent has
	int i, j, k, m, n, update_index, max_index;
	Organism* this_child = NULL;
	Chromosome *this_chromo = NULL;
	Gene* this_gene = NULL;
	GeneDescriptor* gene_desc = NULL;
	char allele_one;
	char allele_two;
	string domPheno;
	string recPheno;
	int genes_left = parser->getGeneCount();
	vector<int> genes_per_chromo;
	vector<int> gene_counts;

	cout << "======================= Results =======================" << endl << endl;
	
	for (i = 0; i < parent->getChromosomeCount(); i++) {
		this_chromo = parent->getChromosome(i);
		genes_per_chromo.push_back(0);
		for (j = 0; j < this_chromo->getGeneCount(); j++) {
			genes_per_chromo.at(i)++;
			genes_left--;
		}
	}

	if (genes_left != 0) {
		cout << "Error! Organism does not match format." << endl;
	}

	m = 0;
	n = 0;

	// Get the gene counts
	for (i = 0; i < count; i++) {
		this_child = parent->getChild(i);
		for (j = 0; j < genes_per_chromo.size(); j++) {
			this_chromo = this_child->getChromosome(j);
			for (k = 0; k < genes_per_chromo.at(j); k++) {
				this_gene = this_chromo->getGene(k);
				allele_one = this_gene->getAlleleOne();
				allele_two = this_gene->getAlleleTwo();

				if (isupper(allele_one) && allele_one == allele_two) {
					n = 0;
				}
				else if (allele_one != allele_two) {
					n = 1;
				}
				else {
					n = 2;
				}

				update_index = (n + 3 * m);
				max_index = gene_counts.size() - 1;
				while (max_index < update_index) {
					gene_counts.push_back(0);
					max_index = gene_counts.size() - 1;
				}

				gene_counts.at(update_index)++;

				m++;
			}
		}
		m = 0;
	}

	// Print the gene counts
	for (j = 0; j < genes_per_chromo.size(); j++) {
		this_chromo = parent->getChromosome(j);
		for (k = 0; k < genes_per_chromo.at(j); k++) {
			this_gene = this_chromo->getGene(k);
			gene_desc = this_gene->getGeneDesc();
			allele_one = gene_desc->getDomAllele();
			allele_two = gene_desc->getRecAllele();
			domPheno = gene_desc->getDomPhenotype();
			recPheno = gene_desc->getRecPhenotype();
			
			cout << "Gene: " << gene_desc->getDescription() << endl;

			cout << "\t" << gene_counts.at(3 * m) << " homozygous dominant (" << domPheno << " " << allele_one << allele_one << ")" << endl;
			cout << "\t" << gene_counts.at(1 + 3 * m) << " heterzygous dominant (" << domPheno << " " << allele_one << allele_two << ")" << endl;
			cout << "\t" << gene_counts.at(2 + 3 * m) << " homozygous recessive (" << recPheno << " " << allele_two << allele_two << ")" << endl << endl;
			m++;
		}
	}

	cout << "A total of " << cross_count << " offspring had at least one crossover gene." << endl << endl;

	return;
}

//-----------------------------------
// Read in the number of offspring
//-----------------------------------
int GeneticsSimView::scanOffspringCount()
{
	int offspring_count = 1001;
	while (offspring_count > 1000 || offspring_count < 0) { // Until the user enters a valid number for the offspring
		cout << "Please enter the number of offspring to be generated (up to 1000):" << endl;
		cin >> offspring_count; // Get the offspring count
	}
	cout << endl;
	return offspring_count;
}

//-----------------------------------
// Read in the file name
//-----------------------------------
string GeneticsSimView::scanFileName()
{
	string filename;
	cout << "Please enter the name of the file containing the simulation data:" << endl;
	cin >> filename;
	cout << endl;
	return filename;
}