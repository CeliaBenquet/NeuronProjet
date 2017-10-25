#include "Neuron.hpp"


//constructeur
//user chooses the Tstart but most of the time 0
Neuron::Neuron (bool exitatory)
: potential_membrane_(POTENTIAL_RESET),tau_(TAU/STEP), c_(C), clock_(0),
  spiked_(false), exitatory_(exitatory)
{
	nbr_spikes_=0;
	spikes_times_.clear();
	delay_buffer_ = { };

	if (exitatory_){
		j_=Je;
	}
	else j_ =Ji; 
}

//destruteur
Neuron::~Neuron(){}

//=======================update=========================================
//update the neuron from time_ to time time_+T avec un pas de 1 (h)
//si neuron a recu un spike update renvoie true
bool Neuron::update(int time)
{
	//on met a jour le spiked_
	spiked_ = false; 
	
	//update le potentiel de membrane
	//sauf si periode de refraction
	if(not isRefractory(time)){
		updatePotential(); 
	}

	//stocker le temps des spikes dans le tableau 
	//si le potentiel est au dessus du seuil (potential_max) emet un spike
	if (potential_membrane_ > POTENTIAL_MAX) {
		spiking(time); 
	}
	else{
		//stocker les potentiels dans un tableau si valeur normale
		potentials_.push_back(potential_membrane_);
	}
	//reset la case correspondante a l intervalle de temps du delay_buffer_
	delay_buffer_[clock_ % delay_buffer_.size()] = 0.0; 
	
	
	//on incremente l horloge interne du neuron 
	++clock_; 
	
	return spiked_; 
}

/*quand spikes : valeur du potentiel = potential max*/

//renvoie true si il est dans son temps de refractory
bool Neuron::isRefractory(int time) {
	return (!((spikes_times_.empty()) or (time > ((spikes_times_.back()/STEP) + REFRACTORY_TIME/STEP)))); 
}

//met a jour le potentiel en ajoutant J
void Neuron::updatePotential(){
	potential_membrane_ = exp(-STEP/(tau_*STEP))*potential_membrane_ + ext_current_*((tau_*STEP)/c_)
							  *(1-exp(-STEP/(tau_*STEP))); 
	//ajoute la valeur dans la case correspondante si jamais reception d un spike a cet intervalle de temps
	potential_membrane_ += delay_buffer_[clock_ % delay_buffer_.size()]; 	

}

void Neuron::spiking(int time){
	potentials_.push_back(POTENTIAL_MAX);
	potential_membrane_ = POTENTIAL_RESET; 
	spikes_times_.push_back(time*STEP); 
	++nbr_spikes_;
	spiked_ = true; 
}

//============================receive===================================

//recoit un spike de potentiel j (positif ou negatif)dans un certain temps delay
/*on a delay_buffer_ un tableau qu on rend circulaire en utlisant le modulo
 *on ajoute une valeur a la case correspondant a l intervalle de temps actuel
 *+ le delai de transmission*/
void Neuron::receiveSpike (int delay , double j){
	delay_buffer_[(clock_ + delay) % delay_buffer_.size()] += j; 	
}

//spikes aleatoirement recu du reste du cerveau
void Neuron::receiveRandom (){
	///a completer
}

//============================getters===================================
vector<double> Neuron::getPotentials() const {return potentials_;} 
vector<double> Neuron::getTimes() const {return spikes_times_;}
double Neuron::getPotentialMembrane() const {return potential_membrane_;}
void Neuron::setPotentialMembrane(double potential) {potential_membrane_=potential;}
double Neuron::getExtCurrent() const{return ext_current_;} 
void Neuron::setExtCurrent(double value){ext_current_=value;} 
int Neuron::getClock() const{return clock_;}
array<double, BUFFER_SIZE> Neuron::getBuffer(){return delay_buffer_;}
bool Neuron::getSpiked() const{return spiked_; } 
int Neuron::getNbrSpikes() const{return nbr_spikes_;}
double Neuron::getJ() const {return j_;}
