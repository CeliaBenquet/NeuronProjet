#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include "Constantes.hpp"
#include <random>

using namespace std; 

/*! @class Neuron 
 * 
 * @brief A neuron that can interact with its environment 
 * 
 */
class Neuron 
{
	public :
		Neuron (bool exitatory, bool test); /**< Constructor */
		~Neuron (); /**<Destructor */
		
		void update(int time); /**< Update function */
		
		vector<double> getTimes() const; /**< Getter of spikes_times_ */
		vector<double> getPotentials() const;  /**< Getter of potentials_ */
		double getPotentialMembrane() const; /**< Getter of potential_membrane_ */
		double getExtCurrent() const;  /**< Getter of ext_current_ */
		void setExtCurrent(double value); /**< Setter of ext_current */
		int getClock() const; /**< Getter of clock_ */
		void setPotentialMembrane(double potentiel); /**< Setter of potential_membrane_ */
		array<double, BUFFER_SIZE> getBuffer(); /**< Getter of delay_buffer_ */
		bool getSpiked() const; /**< Getter of spiked_ */
		int getNbrSpikes() const; /**< Getter of nbr_spikes_ */
		double getJ() const; /**< Getter of j_ */
		void addConnexions(int new_connexion); 
		vector <double> getSpikesTimes() const;
		
		void receiveSpike (int delay , double j); //!< receive the message of the connected neurons that spiked
		void receiveNoise (); //!< receive the random current from the background activity
		vector<int> getConnexions() const; 
	
	private :
		bool test_;
	
		double potential_membrane_; /**< Membrane potential */
		int nbr_spikes_; /**< Count the number of spikes */
		
		double j_;/**< post synaptic potential J when neuron spikes  */
		
		double ext_current_; /**< External Current */
		
		vector <double> spikes_times_; /**< Vector stores the times of the spikes */
		vector <double> potentials_; /**< Vector store the membrane potentials at each step */
		
		bool isRefractory(int time); /**< Boolean function is refractory */
		void spiking(int time); /**< Void function update if spike */
		void updatePotential(); /**< Void function update the membrane potential at each step */

		bool exitatory_; /**< Boolean exitatoy */

		double c_; /**< Membrane capacity */
		int tau_; /**< time interval tau = membrane resistance * membrane capacity */
		
		int clock_; /**< time interval : Internal clock*/
		
		bool spiked_; /**< Boolean has emitted a spike */
		
		array<double, BUFFER_SIZE> delay_buffer_; //!< Array stockes the messages of connected neurons 
		
		vector <int> connexions_; //!< Received connexions of the neuron
 };

#endif
