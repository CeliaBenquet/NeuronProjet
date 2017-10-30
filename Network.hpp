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
 * @brief Set of neurons connected and interracting together
 */
 
class Network
{
	public :
		Network (); /**< Constructor*/
		~Network (); /**< Destructor*/
		
		vector <Neuron*> getNeurons() const; /**< Getter de neurons_ */
		
		void update (int time, ofstream& sortie); /**< Update function */
		vector <int> randomConnections(int a, int b, int nbr_connexion);
		void createConnexions();

		
	private : 
		vector <Neuron*> neurons_;			/**< Table of ptr on neurons */
};

#endif
