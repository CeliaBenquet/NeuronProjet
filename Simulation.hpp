#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "Network.hpp"
#include "Constantes.hpp"
#include <fstream>

/*! @class Simulation 
 * 
 * @brief A simulation of a certain network 
 * 
 * The user can choose the time of the simulation and its objective
 * 
 */

class Simulation 
{
	public :
		Simulation (int n_simulation, double Tstop);
		void run(); 
		
	protected : 
		void printPotential(); 
		void rightSimulation(); 
		void TwoNeurons();
		void OneNeuron(); 

		int Tstop_; ///< number of intervall of time before end of the simulation
		int n_simulation_; ///< number of the simulation
}; 


#endif
