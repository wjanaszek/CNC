#ifndef LICZBYZESPOLONE_H
#define LICZBYZESPOLONE_H

#include <iostream>
#include <vector>

using namespace std;

class liczbyZespolone
{
	public:
		liczbyZespolone();
		liczbyZespolone(double x, double y, char nazwa);
		
		void ustawRe(double x);
		void ustawIm(double y);
		void ustawNazwe(char nazwa);
		char wezNazwe();
		double wezRe();
		double wezIm();
		liczbyZespolone * wezDane();
		liczbyZespolone * znajdzZmienna(int & pom, char nazwaZmiennej, vector <liczbyZespolone> & zmienne);
		void sprzezenie(liczbyZespolone & liczba);
		
		friend liczbyZespolone & operator +(liczbyZespolone & pierwsza, liczbyZespolone & druga);
		friend liczbyZespolone & operator -(liczbyZespolone & pierwsza, liczbyZespolone & druga);
		friend liczbyZespolone & operator *(liczbyZespolone & pierwsza, liczbyZespolone & druga);
		friend liczbyZespolone & operator /(liczbyZespolone & pierwsza, liczbyZespolone & druga);
		liczbyZespolone & operator =(const liczbyZespolone & skad);
		friend ostream & operator <<(ostream & out, liczbyZespolone & doWypisu);
		
	protected:
		double Re;
		double Im;
		char nazwaZmiennej;
};

#endif
