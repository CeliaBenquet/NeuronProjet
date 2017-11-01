#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "Neuron.hpp"
#include "Constantes.hpp"
#include <fstream>

using namespace std; 

/*! @class Network 
 * @brief Set of Neurons connected and interracting together
 * 
 * Each neuron receive a certain number of connections and sends a 
 * potential to all its connected neurons 
 */
 
class Network
{
	public :
		Network (); 
		~Network (); 
		
		vector <Neuron*> getNeurons() const; 
		
		void update (int time, ofstream& spikes_file); 
		vector <int> randomConnectionsExi(int a, int b, int nbr_connexion);
		vector <int> randomConnectionsInh(int a, int b, int nbr_connexion);

		void createConnexions();

		
	protected : 
		vector <Neuron*> neurons_;	/**< Table of all the neurons of the Network*/
};

#endif
