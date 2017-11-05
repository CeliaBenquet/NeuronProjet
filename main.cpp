#include "Constantes.hpp"
#include <iostream>
#include <fstream>
#include "Simulation.hpp"

using namespace std; 


int main() 
{
	int n(0); 
	cout << "Enter the simulation you want to perform (see the read me) : " ; 
	cin >> n;
	Simulation simulation(n, TSTOP/STEP); 
	simulation.run();
	
	return 0;
}



