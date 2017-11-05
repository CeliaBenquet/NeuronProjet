#include "Neuron.hpp"
/*!
 * @brief Constructor 
 * 
 * Value of j_ depends of the type of neuron
 * 
 * @param exitatory boolean to determine the type of neuron inhibitor or exitator
 */
Neuron::Neuron (bool exitatory, bool test)
: exitatory_(exitatory), test_ (test), potential_membrane_(POTENTIAL_RESET), clock_(0),
  spiked_(false),  ext_current_(EXT_CURRENT)
{
	nbr_spikes_=0;
	spikes_times_.clear();
	connexions_.clear();
	
	//all the times of the buffer initialised at 0
	for(auto& i : delay_buffer_){
		i = 0;
	}
	
	//j_ regarding the type of neuron
	if (exitatory_){
		j_=Je;
	}
	else j_=Ji; 
	
	//for the membrane equation
	C1_ = exp(-STEP/TAU);
	C2_ = ((TAU/C)*(1-exp(-STEP/TAU))); 
}

/*!
 * @brief Destructor by default
 * 
 */
Neuron::~Neuron(){}

/*! 
 * @brief Update the neuron 
 * @param time clock of the global simulation 
 * @return boolean value if the neuron spiked in the time interval 
 */
void Neuron::update(int time)
{
	//reinitializes the boolean spiked_
	spiked_ = false; 
	
	//we still need to store the value of the membrane potential
	potentials_.push_back(potential_membrane_);
	
	//if potential higher than maximum potential then spiking
	if (potential_membrane_ > POTENTIAL_MAX) {
		spiking(time); 
	}
	//else we can see if we need to update the potential 
	else{
		 //exept if refractoy time
		if(not isRefractory(time)){
			updatePotential(); 
		}
		//if in refractory time 
		else {
			potential_membrane_=POTENTIAL_RESET; 
			} 
	} 
	//reset the integer value of the buffer corresponding to the interval that just passed
	delay_buffer_[clock_ % delay_buffer_.size()] = 0.0; 
	
	++clock_; 
}


/*!
 * @brief Compute if the neuron is in refracory time at the intervall time
 * 
 * @param time clock of the simulation
 * @return boolean value if the neuorn is in refractory time
 */
bool Neuron::isRefractory(int time) {
	return (!((spikes_times_.empty()) or (time > (spikes_times_.back() + REFRACTORY_TIME/STEP)))); 
}

/*!
 * @brief Update the membrane potential 
 * 
 * first the normal formule
 * then the value of J if message from one of the connected neurons at this time intervall 
 * finally the random current from the background activity 
 */
void Neuron::updatePotential(){
	
		potential_membrane_ = C1_*potential_membrane_ + ext_current_*C2_; 
	
	
	//add the value of the corresponding case if message reception in time intervall
	potential_membrane_ += delay_buffer_[clock_ % delay_buffer_.size()]; 
	
	if(not test_){
		receiveNoise();
	}	
}

/*! 
 * @brief Compute the action to do when neuron is spiking 
 * 
 * add the value of membrane potential to the table
 * reset the membrane potential
 * increase the number of spikes since the bgging of the simulation
 * pass the boolean spiked_ to true 
 * 
 * @param time clock of the simulation to be added to the table of times
 */
void Neuron::spiking(int time){
	potential_membrane_ = POTENTIAL_RESET; 
	spikes_times_.push_back(time); 
	++nbr_spikes_;
	spiked_ = true; 
}

//============================receive===================================

/*!
 * @brief Store the value of the message received from a connected neuron in a certain delay
 * 
 * delay_buffer_ is circular
 * 
 * @param delay the time it takes for the emitted spike to be received
 * @param j the value of the spike that will be received
 */
void Neuron::receiveSpike (int delay , double j){
	delay_buffer_[(clock_ + delay) % delay_buffer_.size()] += j; 
}

/*!
 * @brief Send a random potential to the neuron from the activity background
 * 
 * The random number is chose following the Poisson distribution.
 * This number multiplies the externe potential and is added to the membrane potential.
 */
void Neuron::receiveNoise (){
	static random_device rd;
	static mt19937 generator(rd()); 
	static poisson_distribution<> poisson (NU_EXT*STEP); 
	potential_membrane_ += poisson(generator); 
}

//============================getters===================================
/*! 
 * @brief Getter of vector of membrane potentials
 * @return the vector de potentiels
 */
vector<double> Neuron::getPotentials() const {return potentials_;} 

/*! 
 * @brief Getter of vector of the current membrane potential
 * @return the potential membrane 
 */
double Neuron::getPotentialMembrane() const {return potential_membrane_;}
/*! 
 * @brief Setter of vector of membrane potential
 * @param new value for the potential membrane
 */
void Neuron::setPotentialMembrane(double potential) {potential_membrane_=potential;}
/*! 
 * @brief Getter of external current
 * @return the external current
 */
double Neuron::getExtCurrent() const{return ext_current_;}
/*! 
 * @brief Setter of external current
 * @param new value for the external current
 */ 
void Neuron::setExtCurrent(double value){ext_current_=value;} 
/*! 
 * @brief Getter of the neuron internal clock
 * @return the internal clock
 */
int Neuron::getClock() const{return clock_;}
/*! 
 * @brief Getter of array of the buffer of the future spikes 
 * @return the delay buffer
 */
array<double, BUFFER_SIZE> Neuron::getBuffer(){return delay_buffer_;}
/*! 
 * @brief Getter of boolean spiked 
 * @return the boolean spiked 
 */
bool Neuron::getSpiked() const{return spiked_; } 
/*! 
 * @brief Getter of number of spikes
 * @return integer of the number of spikes
 */
int Neuron::getNbrSpikes() const{return nbr_spikes_;}
/*! 
 * @brief Getter of the post synaptic potential
 * Depends on the type of neuron (exitatory or inhibitory)
 * @return the post synaptic potential J
 */
double Neuron::getJ() const {return j_;}
/*! 
 * @brief Add a value of connection at the end of the table 
 * 
 * @param new_connexion integer number corresponding to the index of a neuron of the Network
 */
void Neuron::addConnexions(int new_connexion){connexions_.push_back(new_connexion);}
/*! 
 * @brief Getter of the connexions_
 * @return table of the connexions to the neuron
 */
vector<int> Neuron::getConnexions() const{return connexions_;} 
/*! 
 * @brief Getter of the times of each spikes
 * @return table of the time of the spikes 
 */
vector <double> Neuron::getSpikesTimes() const {return spikes_times_;} 
