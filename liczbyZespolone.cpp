#include "liczbyZespolone.h"
#include <list>

liczbyZespolone::liczbyZespolone()	{
	Re = 0.0;
	Im = 0.0;
	nazwaZmiennej = '-';
}

liczbyZespolone::liczbyZespolone(double x, double y, char nazwa) : Re(x), Im(y)	{ 
	nazwaZmiennej = nazwa;
}

void liczbyZespolone::ustawRe(double x)
{
	Re = x;
}

void liczbyZespolone::ustawIm(double y)
{
	Im = y;
}

void liczbyZespolone::ustawNazwe(char nazwa)
{
	nazwaZmiennej = nazwa;
}

char liczbyZespolone::wezNazwe()
{
	return nazwaZmiennej;
}

double liczbyZespolone::wezRe()
{
	return Re;
}

double liczbyZespolone::wezIm()
{
	return Im;
}

liczbyZespolone * liczbyZespolone::wezDane()
{
	return this;
}

liczbyZespolone * liczbyZespolone::znajdzZmienna(int & pom, char nazwaZmiennej, vector <liczbyZespolone> & zmienne)
{
	liczbyZespolone * z;
	pom = 0;
	z = new liczbyZespolone(0.0, 0.0, nazwaZmiennej);
	for(int i = 0; i < zmienne.size(); i++)	{
		if(zmienne[i].wezNazwe() == nazwaZmiennej)	{
			*z = zmienne[i];
			pom = 1;
			break;
		}
	}
	return z;
}

void liczbyZespolone::sprzezenie(liczbyZespolone & liczba)
{
	liczba.ustawIm((liczba.wezIm())*(-1));
}

liczbyZespolone & operator +(liczbyZespolone & pierwsza, liczbyZespolone & druga)
{
	liczbyZespolone * wynik;
	wynik = new liczbyZespolone(0.0, 0.0, druga.wezNazwe());
	wynik->ustawRe(pierwsza.wezRe() + druga.wezRe());
	wynik->ustawIm(pierwsza.wezIm() + druga.wezIm());
	return * wynik;
}

liczbyZespolone & operator -(liczbyZespolone & pierwsza, liczbyZespolone & druga)
{
	liczbyZespolone * wynik;
	wynik = new liczbyZespolone(0.0, 0.0, druga.wezNazwe());
	wynik->ustawRe(pierwsza.wezRe() - druga.wezRe());
	wynik->ustawIm(pierwsza.wezIm() - druga.wezIm());
	return * wynik;
}

liczbyZespolone & operator *(liczbyZespolone & pierwsza, liczbyZespolone & druga)
{
	liczbyZespolone * wynik;
	wynik = new liczbyZespolone(0.0, 0.0, druga.wezNazwe());
	wynik->ustawRe(pierwsza.wezRe() * druga.wezRe() - pierwsza.wezIm() * druga.wezIm());
	wynik->ustawIm(pierwsza.wezRe() * druga.wezIm() + druga.wezRe() * pierwsza.wezIm());
	return * wynik;
}

liczbyZespolone & operator /(liczbyZespolone & pierwsza, liczbyZespolone & druga)
{
	liczbyZespolone * wynik;
	liczbyZespolone * sprzezona;
	liczbyZespolone mianownik, licznik;
	
	wynik = new liczbyZespolone(0.0, 0.0, druga.wezNazwe());
	sprzezona = new liczbyZespolone(0.0, 0.0, '-');
	
	sprzezona->ustawRe(druga.wezRe());
	sprzezona->ustawIm(druga.wezIm()*(-1.0));
	
	mianownik = (druga * (*sprzezona));
	licznik = pierwsza * (*sprzezona);
	
	wynik->ustawRe(licznik.wezRe() / mianownik.wezRe());
	wynik->ustawIm(licznik.wezIm() / mianownik.wezRe());
	return * wynik;
}
	
liczbyZespolone & liczbyZespolone::operator =(const liczbyZespolone & skad)
{
	this->Re = skad.Re;
	this->Im = skad.Im;
	this->nazwaZmiennej = skad.nazwaZmiennej;
	return * this;
}

ostream & operator <<(ostream & out, liczbyZespolone & doWypisu)
{
	//Re:
	if(doWypisu.wezRe() > 0.0)	{
		out << "+";
		out << doWypisu.wezRe();
	}
	else if(doWypisu.wezRe() < 0.0)	{
		//out << "-";
		out << doWypisu.wezRe();
	}
	else if((doWypisu.wezRe() == 0.0) && (doWypisu.wezIm() == 0.0))	{
		out << "0";
	}
	
	//Im:
	if(doWypisu.wezIm() > 0.0)	{
		out << "+";
		out << doWypisu.wezIm() << "i";
	}
	else if(doWypisu.wezIm() < 0.0)   {
		//out << "-";
		out << doWypisu.wezIm() << "i";
	}
	return out;
}
