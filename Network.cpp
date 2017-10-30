#include "Network.hpp"
#include <cassert>
#include <random>

/*!
 * @brief Initiate the network to a network of inhibitory and exitatory neurons
 *
 */
Network::Network()
{
	//creation of 12500 neurons some exitatory other inhibitory
	//exitatory
	for(int e(0); e<NE; ++e){
		neurons_.push_back(new Neuron(1, 0));
	}
	//inhibitory
	for (int i(0); i<NI; ++i){
		neurons_.push_back(new Neuron(0, 0));
	}
	
	//on cree un tableau de connexions aleatoires au x neurons du network 
	createConnexions();
	
}

void Network::createConnexions(){
	for(auto& neuron : neurons_){
		for(auto& random_exitatory_connected : randomConnections(0, NE, CE)){
			neuron->addConnexions(random_exitatory_connected); 
		}
		for(auto& random_inhibitory_connected : randomConnections(0, NI, CI)){
			neuron->addConnexions(random_inhibitory_connected); 
		}
		//on verifie que les tableaux font la meme taille 
		assert(neuron->getConnexions().size() == CE+CI); 
	}
}

vector <int> Network::randomConnections(int a, int b, int nbr_connexion){
	static default_random_engine randomGenerator;
	static uniform_int_distribution<int> distNeuron(a,b);
	vector<int> connexions; 
	connexions.clear();
	int i(0);
	do{
		int aleatory (0);
		aleatory = distNeuron(randomGenerator);
		connexions.push_back(aleatory);
		++i;
	} while(i<nbr_connexion);
	
	return connexions;
}

/*!
 * @brief Destructor
 * 
 * Delete the ptr of the neurons_ table at the end of the simulation
 */
Network::~Network() 
{
	for (size_t i (0); i < neurons_.size(); ++i){
		delete neurons_[i];
		neurons_[i] = nullptr;
	}
}

/*!
 * @brief Update the network 
 * 
 * Update each neurons of the network 
 * if they spike send the message to the neurons receivers
 *
 * @param time clock of the simulation,corresponds to  an intervalle
 */
 
void Network::update (int time, ofstream& file){
	
	
	
	for(auto& neuron : neurons_){
		neuron->update(time); 
	}
	
	for(size_t neuron(0); neuron < neurons_.size(); ++neuron){
		for(auto& connexion : neurons_[neuron]->getConnexions()){
			if(neurons_[connexion]->getSpiked()){
				neurons_[neuron]->receiveSpike(DELAY/STEP, neurons_[neuron]->getJ());
			}	
		}
		if(not neurons_[neuron]->getSpikesTimes().empty()){
		file << "Neuron " << neuron+1 << " spikes at " << neurons_[neuron]->getSpikesTimes().back() << endl;
		}
	}		
}

/*!
 * @brief Getter of the table of all the neurones of the Network
 * 
 * @return Table of neurons
 */
 
vector <Neuron*> Network::getNeurons() const {return neurons_;}
