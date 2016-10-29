#include "Interfejs.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

Interfejs::Interfejs()
{
}

bool Interfejs::czyKoniec()
{
	char menu;
	bool czyKoniec;
	cout << "Koniec? T/N ";
	cin >> menu;
	switch(menu)	{
		case 'T':	{		//zakonczenie dzialania programu
			czyKoniec = true;
			break;
		}
		case 't':	{
			czyKoniec = true;
			break;
		}
		case 'N':	{		//uzytkownik chce obliczyc kolejne wyrazenie
			czyKoniec = false;
			break;
		}
		case 'n':	{
			czyKoniec = false;
			break;
		}
		default:	{
			while((menu != 'N') || (menu != 'n') || (menu != 'T') || (menu != 't'))	{
				cout << "Niepoprawne polecenie. Sprobuj jeszcze raz. Koniec? T/N ";
				cin >> menu;
				if((menu == 'T') || (menu == 't'))	{
					czyKoniec = true;
					break;
				}
				if((menu == 'N') || (menu == 'n'))	{
					czyKoniec = false;
					break;
				}
			}
			break;
		}
	}
	return czyKoniec;
}

bool Interfejs::czyJestZmienna(char nazwaZmiennej)
{
	vector <liczbyZespolone> pomocnicza;
	pomocnicza = this->wyniki;
	for(int i = 0; i < pomocnicza.size(); i++)	{
		if(pomocnicza[i].wezNazwe() == nazwaZmiennej)	{
			return true;
			break;
		}
	}
	return false;
}

void Interfejs::edycja(char nazwaZmiennej, const liczbyZespolone & wartosc, vector <liczbyZespolone> & interfejs)
{
	for(int i = 0; i < interfejs.size(); i++)	{
		if(interfejs[i].wezNazwe() == nazwaZmiennej)	{
			interfejs[i] = wartosc;
		}
	}
}

void Interfejs::aktualizuj(char nazwaZmienionej, vector <liczbyZespolone> & interfejs, const vector <char *> & formuly)
{
	int index = 0;
	int dlWejscia = 0;
	char zmiennaObecna;
	for(int i = 0; i < formuly.size(); i++)	{
		for(int j = 1; j < strlen(formuly[i]); j++)	{
			if(formuly[i][j] == nazwaZmienionej)	{
				zmiennaObecna = formuly[i][0];
				stack <char> stos;
				stack <liczbyZespolone> wyniki;
				queue <char *> kolejka;
				dlWejscia = strlen(formuly[i]);
				this->doONP(formuly[i], index, dlWejscia, stos, kolejka);
				//cout << "Po ONP" << endl;
				this->oblicz(wyniki, kolejka, interfejs);
				//cout << "Po obliczeniach" << endl;
				interfejs[i] = wyniki.top();
				interfejs[i].ustawNazwe(zmiennaObecna);
				cout << interfejs[i].wezNazwe() << "=" << interfejs[i] << endl;
			}
		}
	}
}

void Interfejs::wlacz(Interfejs & okno, bool czyPlik)
{
	liczbyZespolone * z;
	char zmienna = '-';
	char zmiennaA = zmienna;
	char zmiennaB = zmienna;
	char menu;
	int dlWejscia = 0;
	int pom, tmp, i = 0;
	bool czyKoniec = false;

	while(czyKoniec == false)	{
		queue <char *> liczby;
		stack <char> operatory;
		stack <liczbyZespolone> wyniki;

		i = 0;
		pom = 0;
		tmp = 0;

		if(czyPlik == false)	{
			dlWejscia = okno.wczytaj(&okno.wejscie);
		}
		else	{
			dlWejscia = okno.wczytajPlik(&okno.wejscie, "test.txt");
			if(dlWejscia == -1)	{
				break;
			}
		}

		if(isalpha(okno.wejscie[0]) != 0)	{
			zmienna = okno.wejscie[0];
			zmiennaA = zmienna;
		}
		okno.doONP(okno.wejscie, i, dlWejscia, operatory, liczby);		//Sprowadzamy wejscie do postaci ONP
		okno.formuly.push_back(okno.wejscie);				

		z = new liczbyZespolone(0.0, 0.0, zmienna);

		okno.oblicz(wyniki, liczby, okno.wyniki);			//Obliczamy wartosc wprowadzonego wyrazenia

		*z = wyniki.top();
		z->ustawNazwe(zmiennaA);

		if(zmienna != '-')	{
			if(okno.czyJestZmienna(zmiennaA) == false)	{
				okno.wyniki.push_back(*z);
			}
			else	{			//edytujemy zmienna
				okno.edycja(zmiennaA, *z, okno.wyniki);
				okno.aktualizuj(zmiennaA, okno.wyniki, okno.formuly);
				tmp = 1;
				//cout << "Zedytowano!" << endl;
			}
		}

		if((zmienna != '-') && (tmp == 0))	{
			//mamy na liscie zdefiniowane zmienne, czekamy na nastepny krok
			queue <char *> liczby;
			stack <char> operatory;
			stack <liczbyZespolone> wyniki;
			liczbyZespolone w;
			liczbyZespolone *w1;
			
			zmienna = '-';

			if(czyPlik == false)	{
				dlWejscia = okno.wczytaj(&okno.wejscie);
			}
			else	{
				dlWejscia = okno.wczytajPlik(&okno.wejscie, "test.txt");
				if(dlWejscia == -1)	{
					break;
				}
			}

			if(isalpha(okno.wejscie[0]) != 0)	{
				zmienna = okno.wejscie[0];
				zmiennaB = zmienna;
			}

			i = 0;
			okno.doONP(okno.wejscie, i, dlWejscia, operatory, liczby);
			okno.formuly.push_back(okno.wejscie);

			z = new liczbyZespolone(0.0, 0.0, zmienna);

			okno.oblicz(wyniki, liczby, okno.wyniki);

			*z = wyniki.top();
			z->ustawNazwe(zmiennaB);

			if(zmienna != '-')	{
				if(okno.czyJestZmienna(zmiennaB) == false)	{
					okno.wyniki.push_back(*z);
				}
				else	{
					okno.edycja(zmiennaB, *z, okno.wyniki);
					okno.aktualizuj(zmiennaB, okno.wyniki, okno.formuly);
					tmp = 1;
				}
			}

			w = *w.znajdzZmienna(pom, zmiennaA, okno.wyniki);
			z = z->znajdzZmienna(pom, zmiennaB, okno.wyniki);

			cout << w.wezNazwe() << " = " << w << endl;
			cout << z->wezNazwe() << " = " << *z << endl;

			czyKoniec = okno.czyKoniec();
			zmienna = '-';
			zmiennaA = zmienna;
			zmiennaB = zmienna;
		}
		else	{
			if(tmp == 0)	{
				cout << *z << endl;
			}
			czyKoniec = okno.czyKoniec();
			zmienna = '-';
		}
	}
}

int Interfejs::wczytaj(char ** wejscie)
{
	string dane;
	cin >> dane;
	(*wejscie) = new char[dane.length() + 1];
	strcpy((*wejscie), dane.c_str());
	return dane.length();
}

int Interfejs::wczytajPlik(char ** wejscie, char * nazwaPliku)
{
	fstream plik;
	string dane;
	plik.open(nazwaPliku, std::ios::in);
	if(plik.eof() == true)	{
		return - 1;
	}
	if(plik.good() == false)	{
		cout << "Wystapil blad przy otwieraniu pliku." << endl;
		return - 1;
	}
	else	{
		getline(plik, dane);
		(*wejscie) = new char[dane.length() + 1];
		strcpy((*wejscie), dane.c_str());
		plik.close();
		cout << "Wczytano: " << *wejscie << endl;
		return dane.length();
	}
}
