#include "Adaline.h"

Adaline::Adaline(double lr)
{
	fstream file;
	file.open("learning_data.txt", ios::in| ios::out);

	if (!file.good()) {
		cout << "ERROR" << endl;
		system("PAUSE");
		exit(0);
	}

	//wczytuj z pliku dopóki sa dane
	while (!file.eof())
		for (int i = 0; i < NUMBER_OF_LETTERS; i++)	//20 liter
		{ 
			for (int j = 0; j < NUMBER_OF_BITS; j++)	// 35 bitow na litere
				file >> letters[i][j];		//wczytywanie danych uczacych

			file >> this->resultTab[i];		//wczytanie z pliku czy dana litera jest duza (1) lub mala (0)
		}

	file.close();

	srand(time(NULL));

	//losowanie wag z zakresu od 0 do 1
	for (int i = 0; i < NUMBER_OF_BITS; i++) {
		weights[i] = double(rand() % 11)/10;
	}

	this->learningRate = lr;

}

//oblicza sume wszystkich wejsc przemnozonych przez wage
double Adaline::calculateSum(int i)
{
	double sum = 0;
	for (int x = 0; x < NUMBER_OF_BITS; x++)
		sum += letters[i][x] * weights[x];

	return sum;

}

int Adaline::uniActivationFunction(double sum)
{
	int result;

	if (sum > 0.5) result = 1;
	else result = 0;

	return result;
}

void Adaline::calculateWeights(int i, double error)
{

	for (int x = 0; x < NUMBER_OF_BITS; x++)
		weights[x] = learningRate * error * letters[i][x] + weights[x];

}


//Funkcja uczaca - progowa unipolarna
void Adaline::uniLearn()
{
	int iter = 0; //licznik iteracji
	bool errorFlag = false; //flaga akceptowanego błędu
	double globalError = 0.0;// błąd globalny
	double localError = 0.0; //błąd lokalny
	double delta = 0.0; //różnica wartości oczekiwanej i otrzymanej sumy
	double sum = 0.0; //zmienna przechowująca sumę bitow i wag
	double threshold = 0.1; //próg uczenia 

	//PROCES UCZENIA

	do {
		iter++; //zwiększenie iteracji (epoki)
		cout << "Iteracja:" << iter << "\t";

		globalError = 0.0; //zerowanie błedu globalngo

		for (int i = 0; i < NUMBER_OF_LETTERS; i++) { //pętla przechodząca po wszystkich literach

			sum = calculateSum(i);

			//obliczanie roznicy pomiedzy wynikiem oczekiwanym a wynikiem otrzymanym
			delta = resultTab[i] - sum;

			//zmiana wartości wag
			calculateWeights(i, delta);

			//aktualizowanie bledu lokalnego i globlanego
			localError = 0.5 * delta * delta;
			globalError += localError;
		}

		cout << "Error: " << globalError << endl;

		if (globalError > threshold)
			errorFlag = true;
		else
			errorFlag = false;


	} while (errorFlag);


}

////////////////////////////////////////////////////////////////////////////////////////////////

//Funkcja aktywacji - funkcja sigmoidalna
double Adaline::sigActivationFunction(double sum) {
	//Wspolczynnik beta = 1.0
	return (1 / (1 + exp(-0.1 * sum)));
}

//Pochodna funkcji aktywcji - funkcji sigmoidalnej
double Adaline::derivativeSigActivationFunction(double sum)
{
	return (0.1*exp(-0.1*sum)) / (pow(exp(-0.1*sum) + 1, 2));
}

//Funkcja uczaca - sigmoidalna unipolarna
void Adaline::sigLearn()
{
	int iter = 0; //licznik iteracji
	bool errorFlag = false; //flaga akceptowanego błędu
	double globalError = 0.0;// błąd globalny
	double localError = 0.0; //błąd lokalny
	double delta = 0.0; //różnica wartości oczekiwanej i otrzymanej sumy
	double sum = 0.0; //zmienna przechowująca sumę bitow i wag
	double output = 0.0;
	double threshold = 0.1; //próg uczenia 

	//PROCES UCZENIA

	do {
		iter++; //zwiększenie iteracji (epoki)
		cout << "Iteracja:" << iter << "\t";

		globalError = 0.0; //zerowanie błedu globalngo

		for (int i = 0; i < NUMBER_OF_LETTERS; i++) { //pętla przechodząca po wszystkich literach

			sum = calculateSum(i);
			output = sigActivationFunction(sum);

			//obliczanie roznicy pomiedzy wynikiem oczekiwanym a wynikiem otrzymanym
			delta = resultTab[i] - output;

			//zmiana wartości wag
			for (int x = 0; x < NUMBER_OF_BITS; x++)
				weights[x] = learningRate * delta * letters[i][x] * derivativeSigActivationFunction(sum) + weights[x];

			//aktualizowanie bledu lokalnego i globlanego
			localError = 0.5 * delta * delta;
			globalError += localError;
		}

		cout << "Error: " << globalError << endl;

		if (globalError > threshold)
			errorFlag = true;
		else
			errorFlag = false;


	} while (errorFlag);


}

//Funkcja testująca
void Adaline::test()
{
	//Znakowa reprezentacja liter
	char testLetters[] = { 'A','B','C','D','E','F','G','H','I','J','a','b','c','d','e','f','g','h','i','j' };

	for (int j = 0; j < NUMBER_OF_LETTERS; j++)
	{

		cout << "Litera '" << testLetters[j] << "': ";
		//Wykorzystanie funkcji aktywacji do sprawdzenia wielkości liter
		if (uniActivationFunction(calculateSum(j)))
			cout << "DUZA";
		else
			cout << "MALA";

		cout << endl;

	}

}