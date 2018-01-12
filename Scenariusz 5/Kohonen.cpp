#include "Kohonen.h"

Kohonen::Kohonen(double N, int size) :N(N), size(size) {

	network = new Neuron[size];
}

void Kohonen::learnNetwork() {

	int index_max = 0;
	double max = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			for (int k = 0; k < size; k++)
			{
				network[k].calculateValue(j);
				if (network[k].output > max)
				{
					max = network[k].output;
					index_max = k;
				}
			}
			network[index_max].adjustWeights(j, i);
			index_max = 0;
			max = 0;
		}
	}
}

void Kohonen::testNetwork(double *tab, int s) {

	int index_max = 0;
	double max = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			network[i].output += (network[i].weights[j] * tab[j]);
			cout << i << " " << j << " " << index_max << endl;
		}
		if (network[i].output > max)
		{
			max = network[i].output;
			index_max = i;
		}
	}

	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << "  " << network[i].output << endl;
	}
}