#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "Neuron.hpp"
#include "Constantes.hpp"
#include "Random.hpp"

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
		
		void update (int time); /**< Update function */
		
	private : 
		vector <Neuron*> neurons_;			/**< Table of ptr on neurons */
		vector <vector<int> > connexions_;	/**< Table of integers corresponding to the number of connexions between 2 neuorns of the Network*/
		random_background_;
};

#endif
