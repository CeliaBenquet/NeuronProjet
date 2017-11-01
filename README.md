# NeuronProjet

NeuronProjet is a project based on the work of Nicolas Brunel in " Dynamics of Sparsely Connected Networks of Excitatory and Inhibitory Spiking Neurons ". It consists in simulating the activity of 12500 neurons of 2 types, exitatory or inhibitory and observe the comportment of the network.

<<<<<<< HEAD
The project can be run from the main. The utilisator can choose which type he wants from the simulations following : Simulation 1: runs the simulation with the parameters from the Constantes.hpp file. Simulation 2: runs the simulation with the parameters from the Constantes.hpp file and displays the evolution of the membrane potential for 4 neurons of the network in the file "membranepotential.txt".

Classes of the project Simulation : allows to run different simualations. Neuron : Represents a neuron and its parameters. Network : Represents a network of neurons

Other files Constants : Regroups differents constants used in all the project. main : Executive file containing the main. The user choose a simulation and the main executes it with the parameters of the Constantes.hpp file. mainTest : regroups differents tests of the project. It is constituted of 3 parts : the tests one 1 neuron, one 2 neurons interacting together and neurons forming a network. The tests are tested with GoogleTest.

To compile First go in the repertory projet1 then do a cmake . then a make. At this point the executories of the Simulation and the tests are ready to be executed. -> ./Neuron : launches the Simulation with the message "Enter the simulation you want to perform" (see before). -> ./Neuron_test : launches a serie of tests.

Complementary tools Doxygen : once you did the cmake, you can do make doc to compile the documentation for Doxygen. Table of plots : to visulise the evolution of the network, the spikes's times of each neurons are saved in a file : "spikes.gdf" during the simulation. To compute the graph, the file must be upload on the data plotter at the adress following : http://cd116-plot.antoinealb.net.
=======
The project can be run from the main. The utilisator can choose which type he wants from the simulations following :
Simulation 1: runs the simulation with the parameters from the Constantes.hpp file.
Simulation 2: runs the simulation with the parameters from the Constantes.hpp file and displays the evolution of the membrane potential for 4 neurons of the network in the file "membranepotential.txt".

Classes of the project 
Simulation : allows to run different simualations.
Neuron : Represents a neuron and its parameters.
Network : Represents a network of neurons 

Other files
Constants : Regroups differents constants used in all the project.
main : Executive file containing the main. The user choose a simulation and the main executes it with the parameters of the Constantes.hpp file.
mainTest : regroups differents tests of the project. It is constituted of 3 parts : the tests one 1 neuron, one 2 neurons interacting together and neurons forming a network. The tests are tested with GoogleTest. 

To compile 
First go in the repertory projet1 then do a cmake . then a make. At this point the executories of the Simulation and the tests are ready to be executed.
-> ./Neuron : launches the Simulation with the message "Enter the simulation you want to perform" (see before).
-> ./Neuron_test : launches a serie of tests.

Complementary tools
Doxygen : once you did the cmake, you can do make doc to compile the documentation for Doxygen.
Table of plots : to visulise the evolution of the network, the spikes's times of each neurons are saved in a file : "spikes.gdf" during the simulation. To compute the graph, the file must be upload on the data plotter at the adress following : http://cd116-plot.antoinealb.net. 
>>>>>>> f179719a40261bf1e85d6c9af06adf0310dac77a
