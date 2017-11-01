#include "Simulation.hpp"

/*!
 * @brief Constructor 
 * 
 * @param n_simulation the number of the simulation the user wants to perform 
 * @param Tstop the time of end of the simualtion 
 */
Simulation::Simulation(int n_simulation, double Tstop)
: Tstop_(Tstop), n_simulation_(n_simulation)
{}

/*!
 * @brief Run the simulation in function of the number of it
 *
 */
void Simulation::run(){
	if (n_simulation_ == 1){
		printPotential(); 
	}
}

/*!
 * @brief Simulation to observe the evolution of the membrane potential 
 * 
 * The membrane potential of 4 neurons are displayed in the file "membranepotentials.txt".
 * 
 *
 */
void Simulation::printPotential(){
	
	int time(TSTART/STEP); 
	Network network;
	
	//open the link to the file to write the potentials values
	ofstream sortie;
	sortie.open("membranepotentials.txt"); 
	sortie << "Membrane potentials in time intervall [" << TSTART 
		   << "," << Tstop_ << "]" <<endl;
	
	//open the link to the file to write the spikes times 	
	ofstream spikes_file;
	spikes_file.open("spikes.gdf");   
	 
	while (time <= Tstop_/STEP){
		
		network.update(time, spikes_file); 
		
		sortie << "P1(" << time*STEP << ")=" << network.getNeurons()[0]->getPotentialMembrane()
			   << " P2(" << time*STEP << ")=" << network.getNeurons()[1]->getPotentialMembrane()		
			   << " P115(" << time*STEP << ")=" << network.getNeurons()[114]->getPotentialMembrane()
			   << " P116(" << time*STEP << ")=" << network.getNeurons()[115]->getPotentialMembrane() << endl;

		++time; 
	}
	
}

