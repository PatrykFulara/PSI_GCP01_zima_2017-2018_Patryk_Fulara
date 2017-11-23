#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

#define NUMBER_OF_BITS 35	 //Liczba bitow reprezentujaca jedna litere
#define NUMBER_OF_LETTERS 20 //Liczba liter

using namespace std;

class Adaline
{
public:
	int resultTab[NUMBER_OF_LETTERS]; //Tablica przechowujaca oczekiwane wyniki
	double weights[NUMBER_OF_BITS]; //Tablica przechowujaca wagi
	int letters[NUMBER_OF_LETTERS][NUMBER_OF_BITS]; //Tablica przechowujaca bitowa reprezentacje liter 
	double learningRate; //Wspolczynnik uczenia

	Adaline(double lr); //Konstruktor przyjmujacy wspolczynnik uczenia
	double calculateSum(int i); //Funkcja zwracajca iloczyn wag i bitow reprezentujacych litere
	int uniActivationFunction(double sum); //Funkcja aktywacji - progowa unipolarna
	double sigActivationFunction(double sum);  //Funkcja aktywacji - sigmoidalna unipolarna
	double derivativeSigActivationFunction(double sum); //Pochodna funkcji aktywacji - sigmoidalnej unipolarnej
	void calculateWeights(int i, double error); //Funkcja aktualizujaca wagi
	void uniLearn(); //Funkcja uczaca - unipolarna
	void sigLearn(); //Funkcja uczaca - sigmoidalna
	void test(); //Funkcja testujaca
	

};