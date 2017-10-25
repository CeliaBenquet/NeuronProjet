#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include "Neuron.hpp"
#include "Constantes.hpp"
#include "Random.hpp"

using namespace std; 

class Network
{
	public :
		Network ();
		~Network (); 
		
		vector <Neuron*> getNeurons() const; 
		
		void update (int time);
		
	private : 
		vector <Neuron*> neurons_;
		vector <vector<int> > connexions_;
		random_background_;
};

#endif
