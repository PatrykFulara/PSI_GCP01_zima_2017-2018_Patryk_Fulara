#include "Neuron.h"

Neuron::Neuron(double learningRate) {
	this->learningRate = learningRate;

	for (int i = 0; i<HOW_MANY_EMOTICONS; i++)
		for (int j = 0; j < HOW_MANY_BITS; j++) {
			weights[i][j] = 0;
			sumOfInput[i] = 0;
			emoticonTest[i] = 0;
		}

	//Losowanie wag pocz¹tkowych z przedzia³u od 0 do 1
	srand(time(NULL));
	for (int i = 0; i<HOW_MANY_BITS; i++) {
		weights[0][i] = (double)rand() / (double)RAND_MAX;
		weights[1][i] = (double)rand() / (double)RAND_MAX;
		weights[2][i] = (double)rand() / (double)RAND_MAX;
		weights[3][i] = (double)rand() / (double)RAND_MAX;
	}

	//Wczytanie danych ucz¹cych
	int whichEmoticon = 0, whichBit = 0, bit;
	fstream file;
	file.open("dane.txt");
	if (file.is_open()) {
		while (!file.eof()) {
			//Jesli wczytano juz wszystkie bity (100) danej emotikony, przejscie do wczytywania bitow kolejnej
			if (whichBit == 225) {
				whichBit = 0; whichEmoticon++;
			}
			//Jesli wczytano wszystkie (4) emotikony, zakoncz wczytywanie
			if (whichEmoticon == HOW_MANY_EMOTICONS)
				break;

			file >> bit;
			emoticons[whichEmoticon][whichBit] = bit;
			whichBit++;
		}
		file.close();
	}

	//Wczytanie danych testuj¹cych
	fstream file2;
	file2.open("dane_test.txt");
	if (file2.is_open()) {
		while (!file2.eof()) {

			if (whichBit == 100) {
				whichBit = 0; whichEmoticon++;
			}
		
			if (whichEmoticon == HOW_MANY_EMOTICONS)
				break;

			file2 >> bit;
			emoticonsTest[whichEmoticon][whichBit] = bit;
			whichBit++;
		}
		file2.close();
	}
}

//Funkcja aktywacji - progowa bipolarna
int Neuron::activationFunction(double sum) {
	return (sum >= 0.5) ? 1 : 0;
}

//Ustawienie sum (wejscie*waga) na wartosc poczatkowa = 0
void Neuron::resetSum() {
	int i = 0;
	for (i = 0; i<HOW_MANY_BITS; i++)
		sumOfInput[i] = 0.;
}

//Uczenie regula Hebba (bez zapominania)
void Neuron::learnDontForget() {
	int epoch = 0; //Epoka

	double globalError = 0.; //Blad globalny
	double localError = 0.; //Blad lokalny
	double MSE = 0.; //Blad sredniokwadratowy
	double MAPE = 0.; //Blad bezwgledny

	double sum = 0.; //Przechowuje sume wejscie*waga (sumOfInput)

	resetSum(); //Ustawienie wartosci poczatkowych dla wektora sumOfInput

	do {
		cout << "Epoka: " << epoch << endl;

		for (int i = 0; i<HOW_MANY_EMOTICONS; ++i) {
			globalError = 0.;
			for (int j = 0; j<HOW_MANY_BITS; ++j) {
				sum = sumOfInput[j];
				sumOfInput[j] = (weights[i][j] * emoticons[i][j]);

				//Aktualizacja wag
				weights[i][j] = weights[i][j] + this->learningRate*sumOfInput[j] * emoticons[i][j];

				if (localError == abs(sum - sumOfInput[j]))
					break;
				localError = abs(sum - sumOfInput[j]);
				globalError = globalError + pow(localError, 2);

			}

			//MSE = pow(globalError, 2) / HOW_MANY_BITS;
			//MAPE = (globalError * 10) / HOW_MANY_BITS;
			//cout << "MSE: " << MSE << "\tMAPE: " << MAPE << "%" << endl;
		}
		epoch++;
		cout << globalError << endl;
	} while (globalError != 0 && epoch < 2000);

	cout << endl << "Liczba epok uczenia [Hebb bez zapominania]: " << epoch << endl;

	test();
}

//Uczenie regu³¹ Hebba (z zapominaniem)
void Neuron::learnForget() {

	int epoch = 0; //Epoka
	double FORGET_RATE = 0.05; //Wspolczynnik zapominania

	double globalError = 0.; //Blad globalny
	double localError = 0.; //Blad lokalny
	double MSE = 0.; //Blad sredniokwadratowy
	double MAPE = 0.; //Blad bezwgledny

	double sum = 0.; //Przechowuje sume wejscie*waga (sumOfInput)

	resetSum(); //Ustawienie wartosci poczatkowych dla wektora sumOfInput

	do {
		cout << "Epoka: " << epoch << endl;

		for (int i = 0; i<HOW_MANY_EMOTICONS; ++i) {
			globalError = 0.;
			for (int j = 0; j<HOW_MANY_BITS; ++j) {
				sum = sumOfInput[j];

				sumOfInput[j] = (weights[i][j] * emoticons[i][j]);

				//Aktualizacja wag
				weights[i][j] = weights[i][j] * (1 - FORGET_RATE) + this->learningRate*sumOfInput[j] * emoticons[i][j];

				if (localError == abs(sum - sumOfInput[j])) break;
				localError = abs(sum - sumOfInput[j]);
				globalError = globalError + pow(localError, 2);
			}

			MSE = pow(globalError, 2) / (HOW_MANY_BITS);
			MAPE = (globalError * 10 / HOW_MANY_BITS);
			cout << "MSE: " << MSE << "\tMAPE: " << MAPE << "%" << endl;

		}

		epoch++;

	} while (globalError != 0 && epoch < 2000);

	cout << endl << "Liczba epok uczenia [Hebb z zapominaniem]: " << epoch << endl;

	test();
}

//Przetestowanie nauczenia danej emotikony
void Neuron::test() {

	double globalError = 0.;
	double localError = 0.;
	double MSE = 0.;
	double MAPE = 0.;
	double sum = 0.;
	int epoch = 0;

	resetSum();

	cout << endl << "Test emotikona USMIECH" << endl;

	do {
		epoch++;
		for (int i = 0; i<HOW_MANY_BITS; i++) {
			sum = sumOfInput[i];
			sumOfInput[i] = (weights[0][i] * emoticonsTest[0][i]);

			emoticonTest[i] = activationFunction(sumOfInput[i]);
			localError = abs(sum - sumOfInput[i]);
			globalError = globalError + pow(localError, 2);
		}

		MSE = pow(globalError, 2) / (HOW_MANY_BITS);
		MAPE = (globalError * 10 / HOW_MANY_BITS);

		//cout << "Uczenie: MSE: " << MSE << "\tMAPE: " << MAPE << "%" << endl;

	} while (globalError != 0 && epoch<1);
	result();

	resetSum();

	cout << endl << "Test emotikona PROSTA" << endl;

	do {
		epoch++;
		for (int i = 0; i<HOW_MANY_BITS; i++) {
			sum = sumOfInput[i];
			sumOfInput[i] = (weights[0][i] * emoticonsTest[1][i]);

			emoticonTest[i] = activationFunction(sumOfInput[i]);
			localError = abs(sum - sumOfInput[i]);
			globalError = globalError + pow(localError, 2);
		}

		MSE = pow(globalError, 2) / (HOW_MANY_BITS);
		MAPE = (globalError * 10 / HOW_MANY_BITS);

		//cout << "Uczenie: MSE: " << MSE << "\tMAPE: " << MAPE << "%" << endl;

	} while (globalError != 0 && epoch<1);

	result();

	resetSum();

	cout << endl << "Test emotikona POCALUNEK" << endl;

	do {
		epoch++;
		for (int i = 0; i<HOW_MANY_BITS; i++) {
			sum = sumOfInput[i];
			sumOfInput[i] = (weights[0][i] * emoticonsTest[2][i]);

			emoticonTest[i] = activationFunction(sumOfInput[i]);
			localError = abs(sum - sumOfInput[i]);
			globalError = globalError + pow(localError, 2);
		}

		MSE = pow(globalError, 2) / (HOW_MANY_BITS);
		MAPE = (globalError * 10 / HOW_MANY_BITS);

		//cout << "Uczenie: MSE: " << MSE << "\tMAPE: " << MAPE << "%" << endl;

	} while (globalError != 0 && epoch<1);

	result();

	resetSum();

	cout << endl << "Test emotikona SMIECH" << endl;

	do {
		epoch++;
		for (int i = 0; i<HOW_MANY_BITS; i++) {
			sum = sumOfInput[i];
			sumOfInput[i] = (weights[0][i] * emoticonsTest[3][i]);

			emoticonTest[i] = activationFunction(sumOfInput[i]);
			localError = abs(sum - sumOfInput[i]);
			globalError = globalError + pow(localError, 2);
		}

		MSE = pow(globalError, 2) / (HOW_MANY_BITS);
		MAPE = (globalError * 10 / HOW_MANY_BITS);

		//cout << "Uczenie: MSE: " << MSE << "\tMAPE: " << MAPE << "%" << endl;

	} while (globalError != 0 && epoch<1);

	result();
}

//Sprawdzenie czy dobrze rozpoznaje emotikony
void Neuron::result() {
	
	int tmp[HOW_MANY_EMOTICONS];

	for (int i = 0; i<HOW_MANY_EMOTICONS; i++)
		tmp[i] = 0;

	for (int i = 0; i<HOW_MANY_BITS; ++i) {
		if (emoticonTest[i] == emoticons[0][i]) tmp[0]++;
		if (emoticonTest[i] == emoticons[1][i]) tmp[1]++;
		if (emoticonTest[i] == emoticons[2][i]) tmp[2]++;
		if (emoticonTest[i] == emoticons[3][i]) tmp[3]++;
	}


	if (tmp[0] > tmp[1] && tmp[0] > tmp[2] && tmp[0] > tmp[3])
		cout << "Wynik: Usmiech";

	if (tmp[1] > tmp[0] && tmp[1] > tmp[2] && tmp[1] > tmp[3])
		cout << "Wynik: Prosta";

	if (tmp[2] > tmp[0] && tmp[2] > tmp[1] && tmp[2] > tmp[3])
		cout << "Wynik: Pocalunek";

	if (tmp[3] > tmp[0] && tmp[3] > tmp[1] && tmp[3] > tmp[2])
		cout << "Wynik: Smiech";
}
