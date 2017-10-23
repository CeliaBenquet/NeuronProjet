#include "Network.hpp"
#include <cassert>

Network::Network()
{
	//on ajoute deux neurons 
	neurons_.push_back(new Neuron()); //0
	neurons_.push_back(new Neuron()); //1

	//on ajoute les connections entre les neurons ici de 0 a 1
	/*pour chaque case 
	 * numero de la case correspond au neuron emetteur
	 * int indexe correspond au neuron receveur*/
	 
	 /// a modifier quand un neuron envoie a plusieurs neurones
	 
	connexions_.push_back({0, 0}); 
	connexions_.push_back({1, 0}); 
	
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
			for (size_t receiver(0); receiver<connexions_[neuron].size(); ++receiver){
				if(connexions_[neuron][receiver] > 0.0){
				/*le neuron d indice correspondant a l int dans la case 
				 * connexion doit recevoir un courant de la part du neuron neuron*/
				neurons_[receiver]->receive(DELAY/STEP, J);
				} 
			}
		}
	} 
}

vector <Neuron*> Network::getNeurons() const {return neurons_;}
