#pragma once
#include "Neuron.h"

class Kohonen {

public:
	Neuron* network;
	double N;
	void learnNetwork();
	void testNetwork(double *tab, int s);
	Kohonen(double N, int size);
	int size;
};
