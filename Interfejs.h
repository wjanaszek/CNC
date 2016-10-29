#ifndef INTERFEJS_H
#define INTERFEJS_H

#include "Kalkulator.h"
#include "liczbyZespolone.h"

#include <stack>
#include <cstdlib>
#include <vector>
#include <queue>

/*
 Klasa obslugujaca operacje wejscia/wyjscia z uzytkownikiem, oprocz tego dokonuje potrzebnych obliczen, korzystajac z metod klasy Kalkulator.
*/
class Interfejs : public Kalkulator
{
	public:
		char * wejscie;
		vector <liczbyZespolone> wyniki;
		vector <char *> formuly;
		
		Interfejs();
		
		bool czyKoniec();
		bool czyJestZmienna(char nazwaZmiennej);
		void edycja(char nazwaZmiennej, const liczbyZespolone & wartosc, vector <liczbyZespolone> & interfejs);
		void aktualizuj(char nazwaZmienionej, vector <liczbyZespolone> & interfejs, const vector <char *> & formuly);
		void wlacz(Interfejs & okno, bool czyPlik);
		int wczytaj(char ** wejscie);
		int wczytajPlik(char ** wejscie, char * nazwaPliku);
};

#endif
