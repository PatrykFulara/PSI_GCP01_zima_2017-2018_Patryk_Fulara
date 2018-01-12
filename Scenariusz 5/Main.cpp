#include<iostream>
#include<cstdlib>
#include<fstream>
#include<list>
#include<ctime>
#include<math.h>
#include "Kohonen.h"

using namespace std;

int main() {

	srand(time(NULL));
	double tab1[4] = { 5.1,	3.5, 1.4, 0.2 };
	double tab2[4] = { 4.9,	3.0, 1.4, 0.2 };
	double tab3[4] = { 7.0,	3.2, 4.7, 1.4 };
	double tab4[4] = { 6.4,	3.2, 4.5, 1.5 };
	double tab5[4] = { 6.3,	3.3, 6.0, 2.5 };
	double tab6[4] = { 5.8,	2.7, 5.1, 1.9 };

	Kohonen network(2, 3);
	network.learnNetwork();

	network.testNetwork(tab1, 4);
	cout << endl;
	network.testNetwork(tab4, 4);
	cout << endl;
	network.testNetwork(tab6, 4);
	cout << endl;

	system("PAUSE");
	return 0;
}