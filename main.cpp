#include <iostream>

#include "Interfejs.h"

int main() {
	Interfejs tmp;
	cout << "Test z pliku" << endl;
	tmp.wlacz(tmp, true);
	cout << "Zakonczono test z pliku. Test reczny" << endl;
	tmp.wlacz(tmp, false);
	cout << "Zakonczono dzialanie" << endl;
	return 0;
}
