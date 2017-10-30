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
	sortie.open("membranepotentials.txt"); 
	sortie << "Membrane potentials in time intervall [" << TSTART 
		   << "," << TSTOP << "]" <<endl;
		  
	ofstream file;
	file.open("spikes.gdf"); 
	 
	while (time <= TSTOP/STEP){
		
		network.update(time, file); 
		
		
		sortie << "P1(" << time*STEP << ")=" << network.getNeurons()[0]->getPotentialMembrane()
			   << "  P2(" << time*STEP << ")=" << network.getNeurons()[1]->getPotentialMembrane()		
			   << " P115(" << time*STEP << ")=" << network.getNeurons()[114]->getPotentialMembrane()
			   << "  P116(" << time*STEP << ")=" << network.getNeurons()[115]->getPotentialMembrane() << endl;

		++time; 
	}
	
	return 0;
}


/*
 * c = 250 pF, 1
 * tau = 10 ms, 20
 * tau ref = 2ms
 * Vreset = -70 mV => apres un spike, 0
 * h = 0.1 ms
 */
