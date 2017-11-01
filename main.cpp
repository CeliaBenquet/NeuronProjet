#include "Constantes.hpp"
#include <iostream>
#include <fstream>
#include "Simulation.hpp"

using namespace std; 


int main(int argc, char **argv) 
{
	
	Simulation simulation(1, TSTOP); 
	simulation.run();
	
	return 0;
}



