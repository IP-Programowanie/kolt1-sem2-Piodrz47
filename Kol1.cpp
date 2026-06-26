#include "Wybor.h"
#include "kolokwium.h"
using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczać pomiędzy #ifdef a #endif. 
*/

#ifdef Kol_1

int main()
{
	Dane d;
	wypelnij(d, 12, 'z', true, false, false, true);
	uint32_t skompresowane = kompresuj(d);
	Dane dekompresowane = dekompresuj(skompresowane);
	if (d == dekompresowane) {
		cout << "dekompresja i kompresja dziala prawidlowo";
	}
	else {
		cout << "dekompresja i kompresja dziala nieprawidlowo";
	}
}

#endif
