#ifndef NEURON_HPP
#define NEURON_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <array>
#include "Constantes.hpp"

using namespace std; 

class Neuron 
{
	public :
		Neuron (bool exitatory); 
		~Neuron ();
		
		bool update(int time); 
		
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
		
		//si recoit un spike on update avec +J
		void receiveSpike (int delay , double j); 
	
	private :
		double potential_membrane_;
		// compte le nombre de spikes
		int nbr_spikes_; 
		
		//courant externe que le neuron recoit		
		double ext_current_; 
		
		//tableau qui stocke les temps ou apparaissent les spikes
		vector <double> spikes_times_; 
		//tableau qui stocke les potentiels
		vector <double> potentials_; 
		
		bool isRefractory(int time); 
		void spiking(int time);
		void updatePotential();


		//capacite membranaire 
		double c_; 
		//tau = resistance membranaire * capacite membranaire
		//un intervalle de temps
		int tau_; 
		
		//horloge du neuron qui commence a sa creation 
		int clock_;
		
		//si emet un spike 
		bool spiked_; 
		
		//stocke les spikes que doit resevoir le neuron
		array<double, BUFFER_SIZE>delay_buffer_; 
 };

#endif
