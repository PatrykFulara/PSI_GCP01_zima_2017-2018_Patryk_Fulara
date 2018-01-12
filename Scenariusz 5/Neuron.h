#pragma once
#include<iostream>
#include<fstream>
#include<ctime>
#include<math.h>
using namespace std;

class Neuron {

public:
	int patternSize;
	int inputSize;
	double **inputs;
	double output;
	double *weights;
	void calculateValue(int index);
	void adjustWeights(int index, int it);
	void drawWeights();
	void normalizeData(double *tab, int size);
	void printWeights();
	double learningCoefficient(int it);
	Neuron();
};