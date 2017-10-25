#include "Network.hpp"
#include <cassert>
#include <random>

Network::Network()
{
	//on crée 12500 neurons certains inhibiteurs d autres exitateurs
	//les exitateurs
	for(int e(0); e<10000; ++e){
		neurons_.push_back(new Neuron(1));
	}
	//les inhibiteurs
	for (int i(0); i<2500; ++i){
		neurons_.push_back(new Neuron(0));
	}
	
	//on ajoute les connections entre les neurons 
	/* pour une case 
	 * les cases verticales representent les neurons qui emettent 
	 * les cases horizontales representent les neurons qui recoivent 
	 * si lignes n1 envoie a colonnes n2 alors 1 dans la case
	 *    N1  N2
	 * N1  0  1
	 * N2  0  0
	 */
	 
	 //on remplit toutes les cases a 0
	 for(int receiver (0); receiver < 12500; ++receiver){
		for (int emetter(0); emetter < 12500; ++emettor){
		connexions_[receiver][emetter] = 0; 
		}
	}
	
	//on remplit 1 si connexion et rien si pas de connexion
	//for (size_t emetter (0); connexion < connexions_.size(); ++emetter){
	for (auto& receiver : connexions_){
		
		//pour les exitateurs
		for(int e(0); e < 10000; ++e){
			//on aura 10% connexions probability. 1 connexion par couple de neurons
			if(bernoulli(EPSILON)){
				receiver[e]=1; 
			}
		}
		//pour les inhibiteurs
		for(int i(10000); i < 12500; ++i){
			//on aura 10% connexions probability. 1 connexion par couple de neurons
			if(bernoulli(EPSILON)){
				receiver[e]=1;
			}
		}
	 }
	
	//on verifie que les tableaux font la meme taille 
	assert(connexions_.size() == neurons_.size()); 
}

Network::~Network() 
{
	for (size_t i (0); i < neurons_.size(); ++i){
		delete neurons_[i];
		neurons_[i] = nullptr;
	}
}

void Network::update (int time){
	//pour chaque neuron du reseau
	for(size_t neuron(0); neuron<neurons_.size(); ++neuron){
		
		//on met a jour le potentiel de membrane du neuron 
		/*si le neuron cible a emis un spike dans l intervalle de temps
		 *on envoie un message au neurons receveurs*/ 
		if(neurons_[neuron]->update(time)) {
			//on parcourt le tableau du neuron correspondant dans le tableau des connexions
			//le int indexe dans le tableau correspond a la case du neuron receveur dans le tableau des neurons
			for (size_t receiver(0); receiver<connexions_.size(); ++receiver){
				///essayer si vraiment necessaire 
				if(connexions_[receiver][neuron] > 0){
				/*le neuron d indice correspondant a l int dans la case 
				 * connexion doit recevoir un courant de la part du neuron neuron*/
				neurons_[receiver]->receiveSpike(DELAY/STEP, neurons_[neuron]->getJ()*connexions_[receiver][neuron]);
				} 
			}
		}
	} 
}

vector <Neuron*> Network::getNeurons() const {return neurons_;}
