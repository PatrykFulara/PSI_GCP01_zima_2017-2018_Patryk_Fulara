#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

int main()
{
	srand(time(NULL));

	const float LEARNING_RATE = 0.001;
	const float THRESHOLD = 0.2;

	int krok = 1;

	//losowanie wag z zakresu -1 do 1
	float w1 = float(rand() % 21) / 10 - 1;
	float w2 = float(rand() % 21) / 10 - 1;

	float error;
	float globalError;

	cout << "LEARNING RATE = " << LEARNING_RATE << endl;
	cout << "THRESHOLD = " << THRESHOLD << endl;

	//dane wejsciowe dla bramki AND
	int inputs[4][3] = {
		{0,0,0},
		{0,1,0},
		{1,0,0},
		{1,1,1}
	};

	int output;

	//tabelka
	cout << "Krok\tx1\tx2\ty\te\tw1\tw2" << endl;
	

	do {
		cout << krok;
		globalError = 0;

		for (int i = 0; i < 4; i++) {

			cout << "\t" << inputs[i][0] << "\t" << inputs[i][1] << "\t";

			//obliczanie wyniku funkcji
			float y = (inputs[i][0] * w1 + inputs[i][1] * w2) - THRESHOLD;

			if (y >= 0) output = 1;
			else output = 0;

			cout << output << "\t";

			//obliczanie bledu
			error = inputs[i][2] - output;
			globalError += abs(error);

			cout << error << "\t";

			if (error) {
				//zmiana wartosci wag
				float deltaW1 = LEARNING_RATE*inputs[i][0] * error;
				float deltaW2 = LEARNING_RATE*inputs[i][1] * error;

				w1 += deltaW1;
				w2 += deltaW2;
			}

			cout << w1 << "\t" << w2 << endl;
		}
		krok++;
	} while (globalError != 0); //dopoki istnieja bledy

	system("PAUSE");
}