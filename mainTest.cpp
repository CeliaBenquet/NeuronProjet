#include "Network.hpp"
#include <iostream>
#include "gtest/include/gtest/gtest.h"
#include "Constantes.hpp"

//tests if membrane potential computed correctly and right time
TEST (NeuronTest, PositiveInput){
	Neuron neuron(1,1); 
	neuron.setExtCurrent(1.0); 

	//test the computation of membrane potentiel
	neuron.update(1);
	EXPECT_EQ(neuron.getExtCurrent()*20.0*(1-exp(-0.1/20)), neuron.getPotentialMembrane()); 
	
	//test after multiple update
	neuron.update(10000);
	//membrane potential should tend to 20
	//the neuron should never spike
	EXPECT_EQ(0, neuron.getNbrSpikes());	
	//the membrane potential should tend naturally towards  with no input 
	neuron.setExtCurrent(0.0);
	//we wait 10 * tau_
	neuron.update(2000);
}	

//tests the times of spiking
TEST (Neuron_test, StandAloneSimulation){
	Neuron neuron(1,1); 
	neuron.setExtCurrent(1.01);
	for (int i(0); i < 4000; ++i){
		neuron.update(i); 
	}
	
	EXPECT_EQ(4, neuron.getNbrSpikes()); 
}

//tests the membrane potential value before and after spiking
TEST (NeuronTest, MembranePotential){
	Neuron neuron(1, 1);
	neuron.setExtCurrent(10.1); 
	
	for(int i(0); i<20; ++i){
		neuron.update(i);
	} 
	//before neuron spikes so less than 20
	EXPECT_NEAR(neuron.getPotentialMembrane(), 19, 2); 
	
	for(int i(8); i<15; ++i){
		neuron.update(i);
	}
	//after neuron spikes during the refractory time
	EXPECT_EQ(neuron.getPotentialMembrane(), 0.0); 

}

//tests the transfer of the potential from one neuron to another for exitatory neurons
TEST (TwoNeurons, NoPSSpikeEXI){
	Neuron neuron1(1,1), neuron2(1,1); 
	int delay (DELAY);
	neuron1.setExtCurrent(1.01);
	//we wait for the first spike and see the impact on neuron2
	for(auto i(0); i<921+delay; i++){
		neuron1.update(i);
		if(neuron1.getSpiked()){
			neuron2.receiveSpike(i + static_cast<unsigned long>(delay), Je);
			//just spiked so refractory time
			EXPECT_EQ(0.0, neuron1.getPotentialMembrane());
		}
		neuron2.update(i); 
 	}
	EXPECT_EQ(0.1, neuron2.getPotentialMembrane()); 
}

//tests the transfer for neurons that already have a potential
TEST (TwoNeurons, WithPSSpikeEXI){
	Neuron neuron1(1, 1), neuron2(1, 1); 
	neuron1.setExtCurrent(1.01);
	neuron2.setExtCurrent(1.0);
	int delay (DELAY);
	
	for (auto i(0); i<1867+delay; i++){
		neuron1.update(i);	
		if(neuron1.getSpiked()){
			neuron2.receiveSpike(i+static_cast<unsigned long>(delay), neuron1.getJ());
			//just spiked so refractory time
			EXPECT_EQ(0.0, neuron1.getPotentialMembrane()); 
		}
		//neuron2 don't have time to reach the treshold
		neuron2.update(i); 
	}
	
	//just before neuron2 spikes 
	EXPECT_EQ(0, neuron2.getNbrSpikes()); 
	neuron2.update(1);
	//just spiked
	EXPECT_EQ(0, neuron2.getPotentialMembrane());
	EXPECT_EQ(1, neuron2.getNbrSpikes()); 
}

//tests the transfer of the potential from one neuron to another for inhibitory neurons
TEST (TwoNeurons, NoPSSpikeINH){
	Neuron neuron1(0,1), neuron2(0,1);  
	neuron1.setExtCurrent(1.01);
	int delay (DELAY); 
	//we wait for the first spike and see the impact on neuron2
	for(auto i(0); i<921+delay; i++){
		neuron1.update(i);
		if(neuron1.getSpiked()){
			neuron2.receiveSpike(i + static_cast<unsigned long>(delay), neuron1.getJ());
			//just spiked so refractory time
			EXPECT_EQ(0.0, neuron1.getPotentialMembrane());
		}
		neuron2.update(i); 
	}
	EXPECT_EQ(-0.5, neuron2.getPotentialMembrane()); 
}

int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
	
}
