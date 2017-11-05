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
	switch(n_simulation_){
			case 1: rightSimulation(); 
					break; 
			case 2: printPotential(); 
					break; 
			case 3: TwoNeurons(); 
					break; 
			case 4: OneNeuron();
					break; 
			default: cout << "This simulation does not exist. Please report to the ReadMe.";
	}
}

/*!
 * @brief Simulation to observe the evolution of the membrane potential 
 * 
 * The membrane potential of 4 neurons are displayed in the file "membranepotentials.txt".
 *
 */
void Simulation::printPotential(){
	
	int time(TSTART/STEP); 
	Network network;
	
	//open the link to the file to write the potentials values
	ofstream sortie;
	sortie.open("membranepotentials.txt"); 
	sortie << "Membrane potentials for each step (in ms) [" << TSTART
		   << "," << Tstop_ << "]" <<endl;
	
	cout << "Simulating..." <<endl; 

	//open the link to the file to write the spikes times 	
	ofstream spikes_file;
	spikes_file.open("spikes.gdf");   
	
	//run the simulation for the Network
	while (time <Tstop_){
		
		network.update(time); 
		cout << time*STEP << flush << endl;
		sortie << "P1(" << time*STEP << ")=" << network.getNeurons()[0]->getPotentialMembrane()
			   << " P2(" << time*STEP << ")=" << network.getNeurons()[1]->getPotentialMembrane()		
			   << " P115(" << time*STEP << ")=" << network.getNeurons()[1114]->getPotentialMembrane()
			   << " P116(" << time*STEP << ")=" << network.getNeurons()[1115]->getPotentialMembrane() << endl;

		++time; 
	}
	
	//Create the file with the spikes times
	cout << "Creation of the spike file... " <<endl;
	for (size_t i(0); i < network.getNeurons().size(); ++i) {	
		for (auto spikeTime : network.getNeurons()[i]->getSpikesTimes()) {	
			spikes_file << spikeTime << "\t" << i + 1 << endl;
		}		
	}
}

/*!
 * @brief Right simulation  
 * 
 * Update of the network during time intervall Tstop-TSTART.
 * Print the times of spiking on a file that can be used to compute a table.
 * 
 */
void Simulation::rightSimulation(){
	
	int time(TSTART/STEP); 
	Network network;
	
	//open the link to the file to write the spikes times 	
	ofstream spikes_file;
	spikes_file.open("spikes.gdf");  
	 
	 cout << "Simulating..." <<endl; 

	 //run the simulation for the Network
	while (time<Tstop_){
			
		network.update(time); 
		
		++time; 
	}
	 
	 //Create the file with the spikes times
	cout << "Creation of the spike file... " <<endl;
	for (size_t i(0); i < network.getNeurons().size(); ++i) {	
		for (auto spikeTime : network.getNeurons()[i]->getSpikesTimes()) {	
			spikes_file << spikeTime << "\t" << i + 1 << endl;
		}
	}
}

/*!
 * @brief Simulation of 2 neurons
 * 
 * Update the Network of 2 neurons with only one connection
 * 
 */
void Simulation::TwoNeurons()
{
		Network n(new Neuron(true, false), new Neuron(true, false)); 
			
		cout << "Simulating..." <<endl; 

		ofstream sortie;
		sortie.open("membranepotentials.txt"); 
		sortie << "Membrane potentials for each step (in ms) [" << TSTART
			   << "," << Tstop_ << "]" <<endl;
		
		int t(TSTART/STEP); 
		while (t<Tstop_){
			n.update(t);
			
			//print the potential in a file
			sortie << "P1(" << t*STEP << ")=" << n.getNeurons()[0]->getPotentialMembrane()
			   << " P2(" << t*STEP << ")=" << n.getNeurons()[1]->getPotentialMembrane()	 <<endl; 	
			
			++t; 
		}
		
		//print the spikes times of the 2 neurons
		for(size_t t(0); t<n.getNeurons().size(); ++t){
			cout << "times when spikes occures for neuron " << t+1 << " : "<<endl;
			for(size_t i(1); i < n.getNeurons()[t]->getSpikesTimes().size(); ++i){
				cout << "Spikes #n " <<i<<"du neurons "<<t+1<<" at: " <<n.getNeurons()[t]->getSpikesTimes()[i]<<endl; 
			}
		}
}

/*!
 * @brief Simulation of 1 neuron
 * 
 * Update the neuron only using the membrane equation.
 * The neuron is in mode testing because it updates itself.
 * It has an extern current.
 * 
 */
void Simulation::OneNeuron(){
	
	Neuron n(true, true);
	n.setExtCurrent(23);
	int t(TSTART/STEP); 
	
	cout << "Simulating..." <<endl; 

	while(t<Tstop_){
		n.update(t);
		
		++t;
	}
	
	//print the spike time
	cout << "times when spikes occures for neuron : "<<endl;
	for(size_t i(1); i < n.getSpikesTimes().size(); ++i){
		cout << "Spikes #n " <<i<<" at: " <<n.getSpikesTimes()[i]<<endl; 
	}
}
