#include "Neuron.h"

Neuron::Neuron() {

	fstream plik;
	plik.open("zbior_uczacy2.txt");
	if (plik.good())
	{
		inputSize = 4;
		patternSize = 30;
		inputs = new double*[patternSize];
		for (int i = 0; i < patternSize; i++)
			inputs[i] = new double[inputSize];

		for (int k = 0; k < patternSize; k++)
		{
			for (int i = 0; i < inputSize; i++)
			{
				inputs[k][i] = 0;
			}
		}

		weights = new double[4];
		for (int i = 0; i < 4; i++)
			weights[i] = 0;

		for (int k = 0; k < patternSize; k++)
		{
			for (int i = 0; i < inputSize; i++)
			{
				plik >> inputs[k][i];
			}
		}

	}
	else
	{
		cout << "blad otwarcia pliku!";
	}
	drawWeights();
}

void Neuron::calculateValue(int index) {

	output = 0;

	for (int i = 0; i < inputSize - 1; i++)
	{
		output += pow(inputs[index][i] - weights[i], 2);
	}
	output = 1 / sqrt(output);
}

void Neuron::drawWeights() {

	double sum = 0;
	for (int i = 0; i < inputSize; i++)
	{
		weights[i] = 5 + (double)rand() / RAND_MAX* (10);
		sum += pow(weights[i], 2);
	}
}

void Neuron::normalizeData(double *tab, int size)
{
	double sum = 0;
	for (int i = 0; i < size; i++)
	{
		sum += pow(tab[i], 2);
	}
	for (int i = 0; i < size; i++)
	{
		tab[i] = (tab[i] / sqrt(sum));
	}
}

void Neuron::printWeights() {

	for (int i = 0; i < inputSize; i++)
	{
		cout << weights[i] << " ";
	}
	cout << endl;
}

void Neuron::adjustWeights(int index, int it) {

	for (int i = 0; i < 4; i++)
	{
		weights[i] = weights[i] + learningCoefficient(it)*(inputs[index][i] - weights[i]);
	}
}

double Neuron::learningCoefficient(int it) {

	return exp(-it / 1000)*0.1;
}