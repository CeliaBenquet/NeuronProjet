#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

#include <string>
#include <iostream>

///times in ms

int const N = 1250; /// number total of neurons
int const NE = 1000; /// number of exitatory neurons
int const NI = 250; /// number of inhibitory neurons
double const EPSILON = 0.1; /// purcentage of connexions  between neurons
int const CE = EPSILON * NE; /// number of connexion to exitatory neurons 
int const CI = EPSILON * NI; /// number of connexions to inhibitory neurons

double const TSTART = 0.0; /// beginning of the simulation in ms 
double const TSTOP = 1000.0;  ///end of the simulation in ms 
double const C =1; /// membrane capacity of a neuron
double const TAU =20; /// membrane capacity * membrane resistance in ms 
double const REFRACTORY_TIME = 2.0; /// time during which no membrane potential update in ms
int const DELAY = 15; /// time of transmission before receiver takes the spike in account in time intervall

double const STEP = 0.1; /// intervall of time 
int const BUFFER_SIZE = 1+DELAY; /// size of the circular delay buffer

double const EXT_CURRENT = 0; /// extern current 
double const POTENTIAL_RESET = 0.0; /// membrane potential at beginning and after spiking
double const POTENTIAL_MAX = 20.0; /// threshold for the membrane potential 
double const G = 5; 
double const Je = 0.1; /// potential sent by exitatory neurons to their receivers
double const Ji = -G*Je; /// potential sent by inhibitory neurons to their receivers
//double const POTENTIAL_EXT = 0.02; /// potential randomly emitted by the activity background 
//double const Ce = 1000; ///extern capacity
//double const NU_EXT = POTENTIAL_EXT*Je*Ce*STEP; /// Nu in the Poisson distribution
double const ETA = 2; /// NuExt/NuThr
double const NU_THR = POTENTIAL_MAX/(Je*TAU); ///Nu Threshold : frequency needed for neuron to reach threshold 
double const NU_EXT = ETA*NU_THR; ///frequency of the activity background

#endif

