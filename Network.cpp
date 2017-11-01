#include "Network.hpp"
#include <cassert>
#include <random>

/*!
 * @brief Initiate a network of inhibitory and exitatory neurons 
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
	
	//creation of a table of all the connexions of the neurons 
	//connexions  
	createConnexions();
	
}

/*!
 * @brief Create a table with random numbers using the uniform distribution.
 * 
 * @param a lower bound 
 * @param b upper bound
 * 
 * @return A table of aleatory numbers
 */
vector <int> Network::randomConnections(int a, int b, int nbr_connexion){

	static random_device rd; 
	static mt19937 gen(rd()); 
	static uniform_int_distribution<int> dist (a, b); 
	
	vector<int> connexions; 
	connexions.clear();
	
	int i(0);
	do{
		int aleatory (0);
		aleatory = dist(gen);
		connexions.push_back(aleatory);
		++i;
	} while(i<nbr_connexion);
	
	return connexions;
}

/*!
 * @brief Create the connexions_ table of each neuron
 * 
 * A connection is from an emitter neuron to the current instance.
 * Those connexions are represented by random numbers. 
 * One number corresponds to the index of a neuron in the neurons_ table.
 * The connexions_ table is constituted of connexions with exitatory then inhibitory neurons.
 * 
 */
 
void Network::createConnexions(){
	for(auto& neuron : neurons_){
		//connections with exitatory
		for(auto& random_exitatory_connected : randomConnections(0, NE, CE)){
			neuron->addConnexions(random_exitatory_connected); 
		}
		//connections with inhibitory
		for(auto& random_inhibitory_connected : randomConnections(0, NI, CI)){
			neuron->addConnexions(random_inhibitory_connected); 
		}
		//verification that the connections_ table is the right size
		assert(neuron->getConnexions().size() == CE+CI); 
	}
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
 * Each neurons of the network are updated. 
 * If the connected neurons spiked, update the delay buffer of the current instance.
 *
 * @param time clock of the simulation, corresponds to an intervalle
 */
 
void Network::update (int time, ofstream& spikes_file){
	
	//update the potential 
	for(auto& neuron : neurons_){
		neuron->update(time); 
	}
	
	for(size_t neuron(0); neuron < neurons_.size(); ++neuron){
		for(auto& connexion : neurons_[neuron]->getConnexions()){
			//if the connected neurons spiked then the current instance update its delay buffer                                                                                                                                                                                                                                                                                                                           
			if(neurons_[connexion]->getSpiked()){
				neurons_[neuron]->receiveSpike(DELAY/STEP, neurons_[neuron]->getJ());
			}	
		}
		if(not neurons_[neuron]->getSpikesTimes().empty()){
		spikes_file << (neurons_[neuron]->getSpikesTimes().back())/STEP << "\t" << neuron+1 << endl;
		}
	}		
}

/*!
 * @brief Getter of the table of all the neurones of the Network
 * 
 * @return Table of neurons
 */
 
vector <Neuron*> Network::getNeurons() const {return neurons_;}
