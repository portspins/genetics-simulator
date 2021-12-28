//---------------------------------------------------------------
// File: GeneticsSimMain.cpp
// Purpose: Demonstrate the processes of inheritance incorporating the Mendelian laws of genetics.
// Author: Matthew Hise
// Date: February 24, 2020
//---------------------------------------------------------------

#include "GeneticsSimView.h"
#include "Organism.h"
#include "GeneticsSimController.h"
#include "GeneticsSimDataParser.h"
#include "Gene.h"
#include "GeneDescriptor.h"

using namespace std;

int main(void) {
	GeneticsSimController *controller = GeneticsSimController::getInstance();
	controller->outputInitialModel();
	controller->generateOffspring();
	system("pause");

	return 0;
}