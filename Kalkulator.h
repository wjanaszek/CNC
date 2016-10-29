#ifndef KALKULATOR_H
#define KALKULATOR_H

#include <list>
#include <stack>
#include <queue>

#include "liczbyZespolone.h"

using namespace std;

/*
 Klasa przeksztalcająca wejscie do postaci ONP. Wykonujaca obliczenia.
*/
class Kalkulator
{
	public:
		virtual void doONP(char * wejscie, int & index, int dlWejscia, stack <char> & stos, queue <char *> & kolejka);
		virtual void znalezionaLiczba(char * wejscie, int & index, queue <char *> & kolejka);
		virtual void znalezionaZmienna(char * wejscie, int & index, queue <char *> & kolejka);
		virtual void znalezioneMnozDziel(char * wejscie, int & index, stack <char> & stos, queue <char *> & kolejka);
		virtual void znalezioneDodOdej(char * wejscie, int & index, stack <char> & stos, queue <char *> & kolejka);
		virtual void znalezioneLewyNawias(char * wejscie, int & index, stack <char> & stos);
		virtual void znalezionyPrawyNawias(char * wejscie, int & index, stack <char> & stos, queue <char *> & kolejka);
		virtual void oblicz(stack <liczbyZespolone> & wyniki, queue <char *> & kolejka, vector <liczbyZespolone> & zmienne);
};

#endif
