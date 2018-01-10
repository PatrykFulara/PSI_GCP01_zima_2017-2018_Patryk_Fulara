#pragma once

#include<ctime>
#include<string>
#include<fstream>
#include<iostream>
#include<string>

#define HOW_MANY_BITS 10*10
#define HOW_MANY_EMOTICONS 4

using namespace std;

class Neuron {
public: 
	int emoticons[4][HOW_MANY_BITS];	//Tablica danych ucz¹cych
	int emoticonsTest[4][HOW_MANY_BITS]; //Tablica danych testuj¹cych
	//0 - Usmiech	1 - Prosta	2 - Pocalunek	3 - Smiech

	double learningRate; //Wspolczynnik uczenia

	double weights[4][HOW_MANY_BITS]; //Wagi 
	double sumOfInput[HOW_MANY_BITS]; //Suma: wagi * dane uczace
	double emoticonTest[HOW_MANY_BITS]; //Tablica do przechowywania wyników w czasie testowania

	Neuron(double); //Konstruktor

	void learnDontForget(); //Uczenie bez zapominania
	void learnForget(); //Uczenie z zapominaniem
	int activationFunction(double); //Funkcja aktywacji (progowa bipolarna)
	void resetSum(); //Ustawienie sum na 0

	void test(); //Testowanie rozpoznawania emotikon
	void result(); //Wypisywanie wyniku testowania

};