//====================================================================
// GeneticsSimDataParser.cpp
// Implementation file for the data parser.
// Author: Dr. Rick Coleman
// Date: December 2009
//====================================================================
#define _CRT_SECURE_NO_WARNINGS

#include "GeneticsSimDataParser.h"
#include <string>


//-----------------------------------
// Constructor
//-----------------------------------
GeneticsSimDataParser::GeneticsSimDataParser()
{
	// Initialize everything
	m_iNumChromosomes = 0;
	m_iNumGenes = 0;
	m_iNextGeneNumber = 0;
	m_iNextChNumP1 = 0;
	m_iNextChNumP2 = 0;
}

//-----------------------------------
// Destructor
//-----------------------------------
GeneticsSimDataParser::~GeneticsSimDataParser()
{
}

//-----------------------------------
// Get the singleton instance
//-----------------------------------
GeneticsSimDataParser *GeneticsSimDataParser::getInstance()
{
	static GeneticsSimDataParser *theInstance = NULL;
	if(theInstance == NULL)
	{
		theInstance = new GeneticsSimDataParser();
	}
	return theInstance;
}

//-----------------------------------
// Initialize the data file
//-----------------------------------
void GeneticsSimDataParser::initDataFile(string fileName)
{
	string line;
	m_sFileName = fileName;

	// Open the data file for reading
	inFile = new ifstream();				// Create an ifstream object
	inFile->open(fileName, fstream::in);	// Open it
	if(inFile->is_open())					// Make sure it is open
	{
		// Get the basic information
		line = getNextLine();
		while(line != "END_OF_FILE")
		{
			if(line == "<GENE>")
			{
				m_iNumGenes++;	// Count all genes
			}
			else if(line == "<GENUS>")
			{
				line = getNextLine(); // Read the genus string
				m_sGenus = line; // Save the genus name
			}
			else if(line == "<SPECIES>")
			{
				line = getNextLine(); // Read the species string
				m_sSpecies = line; // Save the species name
			}
			else if(line == "<CHROMOSOME_COUNT>")
			{
				line = getNextLine(); // Read the chromosome count string
				m_iNumChromosomes = stoi(line); // Save the count
			}
			else if(line == "<COMMON_NAME>")
			{
				line = getNextLine(); // Read the common name string
				m_sCommonName = line; // Save the common name
			}
			line = getNextLine();        // Get the next line
		}
		inFile->close();	// Close the file
		delete inFile;		// Destroy the ifstream object
	}
	else
	{
		cout << "Failed to open file\n";
		cout << "Program terminated.\n\n";
		exit(0);
	}
}

//-----------------------------------
// Get the number of genes
//-----------------------------------
int GeneticsSimDataParser::getGeneCount()
{
	return m_iNumGenes;
}

//-----------------------------------
// Get the number of chromosomes
//-----------------------------------
int GeneticsSimDataParser::getChromosomeCount()
{
	return m_iNumChromosomes;
}

//-----------------------------------
// Get the genus name
//-----------------------------------
string GeneticsSimDataParser::getGenus()
{
	return m_sGenus;
}

//-----------------------------------
// Get the species name
//-----------------------------------
string GeneticsSimDataParser::getSpecies()
{
	return m_sSpecies;
}

//-----------------------------------
// Get the full scientific name
//-----------------------------------
string GeneticsSimDataParser::getScientificName()
{
	// Build the full name just in case it hasn't been done
	m_sSciName = m_sGenus + " " + m_sSpecies;
	return m_sSciName;
}

//-----------------------------------
// Get the common name
//-----------------------------------
string GeneticsSimDataParser::getCommonName()
{
	return m_sCommonName;
}

//--------------------------------------------------------------------------
// Get data on the next gene
// Args:	*trait - pointer to a string to hold the trait name
//			*domDesc - pointer to a string to hold the name of the
//						dominant allele name
//			*domSymbol - pointer to a char variable to hold the dominant
//						trait letter symbol
//			*recDesc - pointer to a string to hold the name of the
//						recessive allele name
//			*recSymbol - pointer to a char variable to hold the recessive
//						trait letter symbol
//			*coChance - pointer to double variable to hold the cross-over
//						probability (range 0.0 to 100.0)
//--------------------------------------------------------------------------
bool GeneticsSimDataParser::getGeneData(string *trait, string *domDesc, char *domSymbol, 
										string *recDesc, char *recSymbol, double *coChance)
{
	int gNum = 0;
	string line;

	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);

	if(inFile->is_open())
	{
		// Read to the the current Gene count
		line = getNextLine();
		while(line != "END_OF_FILE")
		{
			if(line == "<GENE>") // Got one
			{
				if(gNum == m_iNextGeneNumber)
				{
					// Get data on this one
					line = getNextLine();  // Get the next line
					while(line != "END_OF_FILE")
					{
						// Get the gene trait name
						if(line == "<GENE_TRAIT>")
						{
							line = getNextLine();  // Get the next line
							if(line != "END_OF_FILE")
							{
								*trait = line; // Set the trait name
							}
							else
								return false; // Oops!
						}
						else if(line == "<DOMINANT_ALLELE>")
						{
							line = getNextLine();  // Get the next line
							if (line != "END_OF_FILE") {
								*domDesc = line; // Set the dominant allele name
							}
							else
								return false; // Oops!
						}
						else if(line == "<DOMINANT_SYMBOL>")
						{
							line = getNextLine();  // Get the next line
							if (line != "END_OF_FILE")
							{
								*domSymbol = line[0]; // Set the dominant allele symbol
							}
							else
								return false; // Oops!
						}
						else if(line == "<RECESSIVE_ALLELE>")
						{
							line = getNextLine();  // Get the next line
							if (line != "END_OF_FILE")
							{
								*recDesc = line; // Set the recessive allele name
							}
							else
								return false; // Oops!
						}
						else if(line == "<RECESSIVE_SYMBOL>")
						{
							line = getNextLine();  // Get the next line
							if (line != "END_OF_FILE")
							{
								*recSymbol = line[0]; // Set the dominant allele symbol
							}
							else
								return false; // Oops!
						}
						else if(line == "<CROSSOVER_CHANCE>")
						{
							line = getNextLine();  // Get the next line
							if (line != "END_OF_FILE")
							{
								*coChance = stof(line); // Set the cross-over chance
							}
							else
								return false; // Oops!
						}
						else if(line == "</GENE>")
						{
							m_iNextGeneNumber++; // Increment for next call to this function
							inFile->close();
							delete inFile; // Delete the istream object not the file
							return true; // Got it
						}
						line = getNextLine();   // Get the next line
					} // end while
				} // end if(gNum == nextGene)
				else
				{
					gNum++; // Check the next one
				}
			}
			line = getNextLine();  // Get the next line
		}
		inFile->close();
		delete inFile; // Delete the istream object not the file
	} // end if file open
	return false; // If we get here we have got all the genes
}

//--------------------------------------------------------------------------
// Get data on the next chromosome for parent1
// Args:	*strand1 - pointer to a string to hold the strand1
//						genotype description, e.g. "T S".  
//			*strand2 - pointer to a string to hold the strand2
//						genotype description, e.g. "t s".
//  
//						If this is a pea plant with the phenotype of tall 
//						with green seeds.  Its phenotype is heterozygous 
//						tall, and heterozygous green seeds, but these two
//						genes are linked because they are on the same
//						chromosome.
//--------------------------------------------------------------------------
bool GeneticsSimDataParser::getP1Chromosome(string *strand1, string *strand2)
{
	int cNum = 0;
	string line;

	// If we have already gotten all the chromosomes for P1 then return false
	if(m_iNextChNumP1 >= m_iNumChromosomes) return false;

	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if(inFile->is_open())
	{
		line = getNextLine();  // Get the next line
		// Read to the the first parent
		while(line != "END_OF_FILE")
		{
			if(line == "<PARENT>") // Got it
			{
				// Get the next chromosome
				line = getNextLine();  // Get the next line
				while(line != "END_OF_FILE")
				{
					// Get the sensor type
					if(line == "<CHROMOSOME>")
					{
						if(cNum == m_iNextChNumP1) // get this one
						{
							line = getNextLine();  // Get the next line
							while(line != "END_OF_FILE")
							{
								if(line == "<STRAND1>")
								{
									line = getNextLine();  // Get the next line
									if(line != "END_OF_FILE") // Read the genotype string
									{
										*strand1 = line; 
									}
									else
										return false; // Oops!
								}
								else if(line == "<STRAND2>")
								{
									line = getNextLine();  // Get the next line
									if(line != "END_OF_FILE") // Read the genotype string
									{
										*strand2 = line; 
									}
									else
										return false; // Oops!
								}
								else if(line == "</CHROMOSOME>")
								{
									m_iNextChNumP1++;
									inFile->close();
									delete inFile; // Delete the istream object not the file
									return true; // Got one
								}
								line = getNextLine();  // Get the next line
							}
						}
						else
						{
							cNum++;
						}
					}
					line = getNextLine();  // Get the next line
				} // End while(getNextLine)
			} // end if PARENT tag
			line = getNextLine();  // Get the next line
		} // End while(getNextLine)
		inFile->close();
		delete inFile; // Delete the istream object not the file
	} // end if file open
	return false; // If we get here we have got all the chromosomes or failed to open file
}

//--------------------------------------------------------------------------
// Get data on the next chromosome for parent2
// Args:	*strand1 - pointer to a string to hold the strand1
//						genotype description, e.g. "T S".  
//			*strand2 - pointer to a string to hold the strand2
//						genotype description, e.g. "t s".
//  
//						If this is a pea plant with the phenotype of tall 
//						with green seeds.  Its phenotype is heterozygous 
//						tall, and heterozygous green seeds, but these two
//						genes are linked because they are on the same
//						chromosome.
//--------------------------------------------------------------------------
bool GeneticsSimDataParser::getP2Chromosome(string *strand1, string *strand2)
{
	int cNum = 0;
	string line;
	bool foundFirst = false;

	// If we have already gotten all the chromosomes for P2 then return false
	if(m_iNextChNumP2 >= m_iNumChromosomes) return false;

	// Reopen the file
	inFile = new ifstream();
	inFile->open(m_sFileName, fstream::in);
	if(inFile->is_open())
	{
		// Read to the the first parent
		line = getNextLine();  // Get the next line
		while(line != "END_OF_FILE" && !foundFirst)
		{
			if(line == "<PARENT>") // Got it
			{
				foundFirst = true;
			}
			line = getNextLine();  // Get the next line
		}
		// Now Read to the the second parent
		line = getNextLine();  // Get the next line
		while(line != "END_OF_FILE")
		{
			if(line == "<PARENT>") // Got it
			{
				// Get the next chromosome
				line = getNextLine();  // Get the next line
				while(line != "END_OF_FILE")
				{
					// Get the sensor type
					if(line == "<CHROMOSOME>")
					{
						if(cNum == m_iNextChNumP2) // get this one
						{
							line = getNextLine();  // Get the next line
							while(line != "END_OF_FILE")
							{
								if(line == "<STRAND1>")
								{
									line = getNextLine();  // Get the next line
									if(line != "END_OF_FILE") // Read the genotype string
									{
										*strand1 = line; 
									}
									else
										return false; // Oops!
								}
								else if(line == "<STRAND2>")
								{
									line = getNextLine();  // Get the next line
									if (line != "END_OF_FILE") // Read the genotype string
									{
										*strand2 = line; 
									}
									else
										return false; // Oops!
								}
								else if(line == "</CHROMOSOME>")
								{
									m_iNextChNumP2++;
									inFile->close();
									delete inFile; // Delete the istream object not the file
									return true; // Got one
								}
								line = getNextLine();  // Get the next line
							}
						}
						else
						{
							cNum++;
						}
					}
					line = getNextLine();  // Get the next line
				} // End while(getNextLine)
			} // end if PARENT tag
			line = getNextLine();  // Get the next line
		} // End while(getNextLine)
		inFile->close();
		delete inFile; // Delete the istream object not the file
	} // end if file open
	return false; // If we get here we have got all the chromosomes or failed to open file
}

//------------------------------------------------
// Function: getNextLine()
// Purpose: Reads lines from a file and returns them, removing any leading white
//   space.  Skips blank lines. Ignores comment
//   lines starting with <!-- and ending with -->
//------------------------------------------------
string GeneticsSimDataParser::getNextLine()
{
    bool    done = false;
	string tempBuf;
	string buffer;
	char* temp;
    while(!done)
    {
        getline(*inFile, tempBuf); // Read a line from the file

        if(inFile->good())          // If a line was successfully read check it
        {
           if(tempBuf.length() == 0)     // Skip any blank lines
               continue;
		   else if(tempBuf.substr(0, 4) == "<!--") // Skip comment lines
			   continue;
           else done = true;    // Got a valid data line so return with this line
        }
        else
        {
            return "END_OF_FILE";        // Flag end of file
        }
    } // end while
	// Remove white space from end of string and copy remainder of string into the buffer
	temp = &tempBuf[tempBuf.length()]; // point to closing \0
	temp--; // back up 1 space
	while (isspace(*temp))
	{
		*temp = '\0'; // Make it another NULL terminator
		temp--;  // Back up 1 char
	}
	// Remove white space from front of string
	temp = &tempBuf[0];
	while (isspace(*temp)) temp++; // Skip leading white space
	// Copy remainder of string into the buffer
	buffer = temp;
    return buffer;  // Return the line
}