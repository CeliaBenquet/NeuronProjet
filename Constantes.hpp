#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

#include <string>
#include <iostream>



int const N = 1250; ///< number total of neurons
int const NE = 1000; ///< number of exitatory neurons
int const NI = 250; ///< number of inhibitory neurons
double const EPSILON = 0.1; ///< purcentage of connexions  between neurons
int const CE = 100; ///< number of connexion to exitatory neurons 
int const CI = 25; ///< number of connexions to inhibitory neurons

double const TSTART = 0.0; ///< beginning of the simulation
double const TSTOP = 100.0;  ///< end of the simulation
double const STEP = 0.1; ///< intervall of going of time 
double const EXT_CURRENT = 20; ///< extern current when test
double const POTENTIAL_RESET = 0; ///< membrane potential at beginning and after spiking
double const C =1; ///< membrane capacity of a neuron
double const TAU =20; ///< membrane capacity * membrane resistance 
double const POTENTIAL_MAX = 20.0; ///< threshold for the membrane potential 
double const REFRACTORY_TIME = 1.0; ///< time during which no membrane potential update
double const Je = 0.1; ///< potential sent by exitatory neurons to their receivers
double const Ji = -0.5; ///< potential sent by inhibitory neurons to their receivers
int const DELAY = 15; ///< time of transmission before receiver takes the spike in account
int const BUFFER_SIZE = 1+DELAY; ///< size of the circular delay buffer
int const G = -Ji/Je; ///< ratio of the emitted potentials 
double const POTENTIAL_EXT = 0.1; ///< potential randomly emitted by the activity background 
double const ETA = 2; ///< 


#endif

