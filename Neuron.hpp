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
		Neuron (bool exitatory, bool test); 
		~Neuron (); 
		
		void update(int time); 
		
		vector<double> getTimes() const; 
		vector<double> getPotentials() const;  
		double getPotentialMembrane() const; 
		double getExtCurrent() const;  
		void setExtCurrent(double value); 
		int getClock() const; 
		void setPotentialMembrane(double potentiel); 
		array<double, BUFFER_SIZE> getBuffer(); 
		bool getSpiked() const; 
		int getNbrSpikes() const; 
		double getJ() const;
		void addConnexions(int new_connexion); 
		vector <double> getSpikesTimes() const;
		
		void receiveSpike (int delay , double j); 
		void receiveNoise (); 
		vector<int> getConnexions() const; 
	
	protected :		
		bool isRefractory(int time); 
		void spiking(int time); 
		void updatePotential(); 

		bool test_; ///< Allows to put a test mode with no random activity
	
		double potential_membrane_; /**< Membrane potential */
		int nbr_spikes_; /**< Count the number of spikes */
		
		double j_;/**< post synaptic potential J when neuron spikes  */
		
		double ext_current_; /**< External Current */
		
		vector <double> spikes_times_; /**< Vector stores the times of the spikes */
		vector <double> potentials_; /**< Vector store the membrane potentials at each step */
		
		bool exitatory_; /**< Boolean exitatoy */

		double c_; /**< Membrane capacity */
		int tau_; /**< time interval tau = membrane resistance * membrane capacity */
		
		int clock_; /**< time interval Internal clock*/
		
		bool spiked_; /*!< Boolean has emitted a spike */
		
		array<double, BUFFER_SIZE> delay_buffer_; //!< Array stockes the messages of connected neurons 
		
		vector <int> connexions_; //!< Received the connexions of the neuron
 };

#endif
