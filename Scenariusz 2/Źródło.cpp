#include "Adaline.h"


int main()
{
	double learningRate = 0.1;

	//Tworzenie, uczenie i testowanie Adaline - funkcja progowa unipolarna
	cout << "FUNKCJA PROGOWA UNIPOLARNA." << endl;
	Adaline adaline1(learningRate);
	adaline1.uniLearn();
	adaline1.test();

	cout << "FUNKCJA SIGMOIDALNA UNIPOLARNA." << endl;
	//Tworzenie, uczenie i testowanie Adaline - funkcja sigmoidalna unipolarna
	Adaline adaline2(learningRate);
	adaline2.sigLearn();
	adaline2.test();
	

	cout << endl;
	system("PAUSE");
	return 0;
}
