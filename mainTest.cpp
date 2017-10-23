#include "Network.hpp"
#include <iostream>
#include "gtest/include/gtest/gtest.h"
#include "Constantes.hpp"

//teste si potentiel de membrane computed correctly and right time
TEST (Neuron, PositiveInput){
	Neuron neuron (1.0); 

	//test the computation of membrane potentiel
	neuron.update(1);
	EXPECT_EQ(TAU*(1.0-exp(-STEP/TAU)), neuron.getPotentialMembrane()); 
	
	//test after multiple update
	/*neuron.update(10000);
	membrane potential should tend to 20
	the neuron should never spike
	EXPECT_EQ(0, neuron.getNbrSpikes());
	EXPECT_GT(1E-3, fabs(19.999 -neuron.getPotentialMembrane()));
	
	the membrane potential should tend naturally towards  with no input 
	neuron.setExtCurrent(0.0);
	we wait 10 * tau_
	neuron.update(2000);
	EXPECT_NEAR(0, neuron.getPotentialMembrane(), 1E-3);*/
}	

TEST (Neuron, NegativeInput){
	/*Neuron neuron(1.0);
	
	neuron.update(943); */

}

int main(int argc, char **argv) 
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
	
}
