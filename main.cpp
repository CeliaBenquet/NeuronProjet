#include "Constantes.hpp"
#include "Network.hpp"
#include <iostream>
#include <fstream>

using namespace std; 

//pour le temps : 1 int = 1 ms

int main(int argc, char **argv) 
{
	
	int time(TSTART/STEP); 
	Network network;
	
	ofstream sortie;
	sortie.open("membrane_potentials.txt"); 
	sortie << "Potentiels de membrane sur l intervalle de temps [" << TSTART 
		   << "," << TSTOP << "]" <<endl;
		   
	while (time <= TSTOP/STEP){
		network.update(time); 
		sortie << "P1(" << time*STEP << ") = " << network.getNeurons()[0]->getPotentialMembrane()
			   << "  P2(" << time*STEP << ") = " << network.getNeurons()[1]->getPotentialMembrane() << endl;
		++time; 
	}
	
	cout << " jai fonctionneeeeee" <<endl; 
	return 0;
}


/*
 * c = 250 pF, 1
 * tau = 10 ms, 20
 * tau ref = 2ms
 * Vreset = -70 mV => apres un spike, 0
 * h = 0.1 ms
 */
