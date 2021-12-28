//====================================================================
// GeneticsSimDataParser.h
// Interface file for the data parser.
// Author: Dr. Rick Coleman
// Modified by: Matthew Hise
// Date: December 2009
//====================================================================

#pragma once

#include <fstream>
#include <iostream>

using namespace std;

class GeneticsSimDataParser
{
	private:
		ifstream	*inFile;				// Genetics sim data definition file
		int			m_iNumChromosomes;		// Number of chromosomes in the test organism
		int			m_iNumGenes;			// Number of master genes
		int			m_iNextGeneNumber;		// Next master gene number
		int			m_iNextChNumP1;			// Next chromosome number for parent 1
		int			m_iNextChNumP2;			// Next chromosome number for parent 2
		string      m_sFileName;			// Data file name
		string		m_sGenus;    			// Genus name of this test organism
		string		m_sSpecies; 			// Species name of this test organism
		string		m_sSciName;  			// Full scientific name of the test organism
		string		m_sCommonName;   		// Common use name of the test organism

		GeneticsSimDataParser();			// Private Constructor

	public:
		~GeneticsSimDataParser();				// Destructor
		static GeneticsSimDataParser *getInstance();	// Get the singleton instance
		void initDataFile(string fileName);
		int getChromosomeCount();
		int getGeneCount();
		string getGenus();
		string getSpecies();
		string getScientificName();
		string getCommonName();
		bool getP1Chromosome(string *strand1, string *strand2);
		bool getP2Chromosome(string *strand1, string *strand2);
		bool getGeneData(string *trait, string *domDesc, char *domSymbol,
			string *recDesc, char *recSymbol, double *coChance);
	private:
		string getNextLine();

};