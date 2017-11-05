#include "Network.hpp"
#include <cassert>
#include <random>

/*!
 * @brief Initiate a network of inhibitory and exitatory neurons 
 *
 * network for more than 2 neurons
 * 
 */
Network::Network()
{
	cout << "Creating the network..." <<endl;
	//creation of 12500 neurons some exitatory other inhibitory
	//exitatory
	for(int e(0); e<NE; ++e){
		neurons_.push_back(new Neuron(true, false));
	}
	//inhibitory
	for (int i(0); i<NI; ++i){
		neurons_.push_back(new Neuron(false, false));
	}
	
	assert(neurons_.size() == NI+NE); 

	//creation of a table of all the connexions of the neurons 
	createConnexions();
}

/*!
 * @brief Initiate a network of 2 neurons 
 *
 * network of 2 neurons with the first one connected (emits signal) to the second
 * 
 * @param n1 pointer on the first neuron of the Network
 * @param n2 pointer on the second neuron of the Network
 */
Network::Network(Neuron* n1, Neuron* n2){
	
	cout << "Creating the network..." <<endl;
	neurons_.push_back(n1);
	neurons_.push_back(n2);
	n1->addConnexions(1); 
	
}

/*!
 * @brief Create a table with random numbers using the uniform distribution.
 * 
 * connections for excitatory neurons
 * 
 * @param a lower bound 
 * @param b upper bound
 * 
 * @return A table of aleatory numbers
 */
vector <int> Network::randomConnectionsEXC(int a, int b, int nbr_connexion){

	static random_device rd; 
	static mt19937 gen1(rd()); 
	static uniform_int_distribution<int> dist1 (a, b); 
	
	vector<int> connexions; 
	connexions.clear();
	
	int i(0);
	int aleatory (0);
	while(i<nbr_connexion){
		aleatory = dist1(gen1);
		dist1.reset();
		connexions.push_back(aleatory);
		++i;
	} 
	
	return connexions;
}

/*!
 * @brief Create a table with random numbers using the uniform distribution.
 * 
 * connections for inhibitory neurons
 * 
 * @param a lower bound 
 * @param b upper bound
 * 
 * @return A table of aleatory numbers
 */
vector <int> Network::randomConnectionsINH(int a, int b, int nbr_connexion){

	static random_device rd; 
	static mt19937 gen2(rd()); 
	static uniform_int_distribution<int> dist2 (a, b); 
		
	vector<int> connexions; 
	connexions.clear();
	
	int i(0);
	int aleatory (0);
	while(i<nbr_connexion){
		aleatory = dist2(gen2);
		dist2.reset();
		connexions.push_back(aleatory);
		++i;
	}
	
	
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
	for (size_t i(0); i < neurons_.size(); ++i){
		vector<int> exc = randomConnectionsEXC(0, NE-1, CE);
		vector<int> inh = randomConnectionsINH(NE, NE+NI-1, CI);
		
		assert(exc.size()==CE);
		assert(inh.size()==CI);

		//connections with excitatory
		for (auto& random_excitatory_source : exc){
			neurons_[random_excitatory_source]->addConnexions(i);
			
			assert (random_excitatory_source>-1);
			assert (random_excitatory_source<NE);
		}

		//connections with inhibitory
		for (auto& random_inhibitory_source : inh){
			neurons_[random_inhibitory_source]->addConnexions(i);

			assert(random_inhibitory_source>NE-1);
			assert(random_inhibitory_source<NI+NE);
		}
	}
	//the table of connexions correspond to the emitions. 
	//its size is random.
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
 
void Network::update (int time){
	
	for (size_t i(0); i < neurons_.size(); ++i) {
		Neuron* neuron = neurons_[i];
		
		//update each neuron
		neuron->update(time);
		
		//if this neuron spiked 
		if (neuron->getSpiked()) {
			for (auto& target : neuron->getConnexions()) {
				//each target receive a spike of value j_
				neurons_[target]->receiveSpike(DELAY, neuron->getJ());
			}
		}	
	}	
}

/*!
 * @brief Getter of the table of all the neurones of the Network
 * 
 * @return Table of neurons
 */
 
vector <Neuron*> Network::getNeurons() const {return neurons_;}
