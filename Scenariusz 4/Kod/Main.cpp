#include "Neuron.h"

int main() {

	const double LEARNING_RATE = 1;


	Neuron hDontForget(LEARNING_RATE);
	hDontForget.learnDontForget();

	//Neuron hForget(LEARNING_RATE);
	//hForget.learnForget();


	cout << endl << "Wspolczynnik uczenia: " << LEARNING_RATE << endl << endl;

	system("pause");

	return 0;
}