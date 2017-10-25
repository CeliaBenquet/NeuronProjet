#include "Network.hpp"
#include <iostream>
#include "gtest/include/gtest/gtest.h"
#include "Constantes.hpp"

//teste si potentiel de membrane computed correctly and right time
/*TEST (NeuronTest, PositiveInput){
	Neuron neuron; 
	neuron.setExtCurrent(1.0); 

	//test the computation of membrane potentiel
	neuron.update(1);
	EXPECT_EQ(TAU*(neuron.getExtCurrent()-exp(-STEP/TAU)), neuron.getPotentialMembrane()); 
	
	//test after multiple update
	neuron.update(10000);
	//membrane potential should tend to 20
	//the neuron should never spike
	EXPECT_EQ(0, neuron.getNbrSpikes());
	//EXPECT_GT(1E-3, fabs(19.999 -neuron.getPotentialMembrane()));
	
	//the membrane potential should tend naturally towards  with no input 
	neuron.setExtCurrent(0.0);
	//we wait 10 * tau_
	neuron.update(2000);
	//EXPECT_NEAR(0, neuron.getPotentialMembrane(), 10E-3);
}	*/

TEST (Neuron_test, StandAloneSimulation){
	Neuron neuron; 
	neuron.setExtCurrent(1.01);
	
			bool spike = neuron.update(4000);

	EXPECT_EQ(4, neuron.getNbrSpikes()); 
}

/*TEST (TwoNeurons, NoPSSpike){
	Neuron neuron1, neuron2; 
	int delay (DELAY);
	neuron1.setExtCurrent(1.01);
	//we wait for the first spike and see the impact on neuron2
	for(auto i(0); i<925+delay; i++){
		if(neuron1.update(1)){
			neuron2.receiveSpike(i + static_cast<unsigned long>(delay), 0.1);
			EXPECT_EQ(0.0, neuron1.getPotentialMembrane());
		}
		neuron2.update(1); 
	}
	
	EXPECT_EQ(0.1, neuron2.getPotentialMembrane()); 
}*/

/*TEST (TwoNeurons, WithPSSpike){
	Neuron neuron1, neuron2; 
	neuron1.setExtCurrent(1.01);
	neuron2.setExtCurrent(1.0);
	int delay (DELAY);
	//neurons did not have time to reach the treshold 
	for (auto i(0); i<1869+delay; i++){
		if(neuron1.update(1)){
			neuron2.receiveSpike(i+static_cast<unsigned long>(delay), 0.1);
			EXPECT_EQ(0.0, neuron1.getPotentialMembrane()); 
		}
		neuron2.update(1); 
	}
	
	//just before neuron2 spikes 
	EXPECT_EQ(0, neuron2.getNbrSpikes()); 
	neuron2.update(1);
	EXPECT_EQ(0, neuron2.getPotentialMembrane());
	///on veut que des que spiker retourne a 0
	EXPECT_EQ(1, neuron2.getNbrSpikes()); 
}*/


int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
	
}
