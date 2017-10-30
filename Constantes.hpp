#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

#include <string>
#include <iostream>

//constantes 
int const N = 125; //!< number total of neurons
int const NE = 100; //!< number of exitatory neurons
int const NI = 25; //!< number of inhibitory neurons
double const EPSILON = 0.1; //!< purcentage of connexions  between neurons
int const CE = 10; //!< number of connexion to exitatory neurons 
int const CI = 3; //!< number of connexions to inhibitory neurons

double const TSTART = 0.0; //temps de debut de l activite du neurone
double const TSTOP = 10.0;  //temps jusqu'a laquelle doit aller la simulation
double const STEP = 0.1; //pas d avancee du temps
double const EXT_CURRENT = 20; //valeur courant externe
double const POTENTIAL_RESET = 0; //potential apres que le seuil a ete atteint
double const C =1; //capacite membranaire d un neurone
double const TAU =20; // c*r
double const POTENTIAL_MAX = 20.0; //est atteint quand firing threshold (tau)
double const REFRACTORY_TIME = 1.0; //temps ou on met pas a jour le potentiel
double const Je = 0.1; //potentiel envoyé par un neuron a un autre
double const Ji = -0.5; //potentiel du spike des neurons inhibiteurs attention NEGATIF
double const Jext = 0.1; 
int const DELAY = 15; //temps de transmission avant que l autre neuron recoive le spike
int const BUFFER_SIZE = 1+DELAY; //taille du tableau circulaire
int const G = Ji/Je; 
double const POTENTIAL_EXT = 0.002; //Vext qui vient du random background  
double const MU = 2;


#endif

