#include "Kalkulator.h"

#include <iostream>
#include <queue>
#include <stack>
#include <cstdlib>
#include <cstring>
#include <string>
#include <string.h>
#include <cstdio>

using namespace std;

void Kalkulator::doONP(char * wejscie, int & index, int dlWejscia, stack <char> & stos, queue <char *> & kolejka)
{
	char * tmpLiczba;
	char * doKolejki;
	int i, j = 0;
	int dlLiczby = 0;
	char tmp;
	if(index < dlWejscia)	{
		if(isdigit(wejscie[index]) != 0)	{		//symbol jest liczba
			this->znalezionaLiczba(wejscie, index, kolejka);
		}
		else if((wejscie[index] == '*') || (wejscie[index] == '/'))	{
			this->znalezioneMnozDziel(wejscie, index, stos, kolejka);
		}
		else if((wejscie[index] == '+') || (wejscie[index] == '-'))	{
			this->znalezioneDodOdej(wejscie, index, stos, kolejka);
		}
		else if(wejscie[index] == '(')	{
			this->znalezioneLewyNawias(wejscie, index, stos);
		}
		else if(wejscie[index] == ')')	 {
			this->znalezionyPrawyNawias(wejscie, index, stos, kolejka);
		}
		else if(isalpha(wejscie[index]) != 0)	{
			this->znalezionaZmienna(wejscie, index, kolejka);
		}
		doONP(wejscie, index, dlWejscia, stos, kolejka);
	}
	else	{
		while(stos.empty() == false)	{
			tmp = stos.top();
			if(tmp == ')')	{
				while((stos.empty() == false) && (stos.top() != '('))	{
					if(stos.top() != '(')	{
						tmp = stos.top();
						doKolejki = new char[2];
						doKolejki[0] = tmp;
						doKolejki[1] = '\0';
						stos.pop();
						kolejka.push(doKolejki);
					}
					else	{
						stos.pop();
						break;
					}
				}
			}
			doKolejki = new char[2];
			doKolejki[0] = tmp;
			doKolejki[1] = '\0';
			stos.pop();
			kolejka.push(doKolejki);
		}
	}
}

void Kalkulator::znalezionaLiczba(char * wejscie, int & index, queue <char *> & kolejka)
{
	int i, j, pom, dlLiczby = 0;
	char * tmpLiczba;
	if(isdigit(wejscie[index]) != 0)	{		//symbol jest liczba
		i = index;
		j = i;
		while((isdigit(wejscie[i]) != 0) || (wejscie[i] == '.'))		{
			i++;
		}
		if(wejscie[i] == 'i')	{
			//cout << "Zespolona" << endl;
			//dlLiczby = i;
			pom = 1;
		}
		else	{
			dlLiczby = i - index;
			pom = 0;
		}
		index = i;
		i = j;
		j = 0;
		tmpLiczba = new char[dlLiczby + 1];
		if(pom == 1)	{
			while(i <= index)	{
				tmpLiczba[j] = wejscie[i];
				i++;
				j++;
			}
			index = i;
			tmpLiczba[j] = 'i';
		}
		else if(pom == 0)	{
			while(i < index)	{
				tmpLiczba[j] = wejscie[i];
				i++;
				j++;
			}
		}
		tmpLiczba[j] = '\0';
		kolejka.push(tmpLiczba);
	}
}

void Kalkulator::znalezionaZmienna(char * wejscie, int & index, queue <char *> & kolejka)
{
	char * doKolejki;
	doKolejki = new char[2];
	doKolejki[0] = wejscie[index];
	doKolejki[1] = '\0';
	kolejka.push(doKolejki);
	if(index == 0)	{
		index = index + 2;
	}
	else	{
		index++;
	}
}

void Kalkulator::znalezioneMnozDziel(char * wejscie, int & index, stack <char> & stos, queue <char *> & kolejka)
{
	char tmp;
	char * doKolejki;
	if(stos.empty() == true)	{
		stos.push(wejscie[index]);
		index++;
	}
	else	{
		if((stos.top() == '+') || (stos.top() == '-') || (stos.top() == ')') || (stos.top() == '('))	{
			stos.push(wejscie[index]);
			index++;
		}
		else	{
			while(stos.empty() == false)	{
				tmp = stos.top();
				doKolejki = new char[2];
				doKolejki[0] = tmp;
				doKolejki[1] = '\0';
				stos.pop();
				kolejka.push(doKolejki);
			}
			stos.push(wejscie[index]);
			index++;
		}
	}
}

void Kalkulator::znalezioneDodOdej(char * wejscie, int & index, stack <char> & stos, queue <char *> & kolejka)
{
	char tmp;
	char * doKolejki;
	if(stos.empty() == false)	{
		while((stos.empty() == false) && ((stos.top() == '*') || (stos.top() == '/') || (stos.top() == '+') || (stos.top() == '-')))	{ 
			tmp = stos.top();
			doKolejki = new char[2];
			doKolejki[0] = tmp;
			doKolejki[1] = '\0';
			stos.pop();
			kolejka.push(doKolejki);
		}
	}
	stos.push(wejscie[index]);
	index++;
}

void Kalkulator::znalezioneLewyNawias(char * wejscie, int & index, stack <char> & stos)
{
	stos.push(wejscie[index]);
	index++;
}

void Kalkulator::znalezionyPrawyNawias(char * wejscie, int & index, stack <char> & stos, queue <char *> & kolejka)
{
	char tmp;
	char * doKolejki;
	while(stos.empty() == false)	{
		if(stos.top() != '(')	{
			tmp = stos.top();
			doKolejki = new char[2];
			doKolejki[0] = tmp;
			doKolejki[1] = '\0';
			stos.pop();
			kolejka.push(doKolejki);
		}
		else	{
			//cout << "Znaleziono koniec nawiasu" << stos.top() << endl;
			stos.pop();
			break;
		}
	}
	index++;
}

void Kalkulator::oblicz(stack <liczbyZespolone> & wyniki, queue <char *> & kolejka, vector <liczbyZespolone> & zmienne)
{
	char * tmp, * liczba;
	char nazwaZmiennej;
	queue <char *> pomocnicza;
	int i, j, k, Re, Im, pom = 0;
	double tmpD = 0.0;
	liczbyZespolone * z;
	liczbyZespolone a, b;
	while(kolejka.empty() == false)	{
		pom = 0;
		tmp = new char[strlen(kolejka.front()) + 1];
		strcpy(tmp, kolejka.front());
		if(isalpha(tmp[0]) != 0)	{
			nazwaZmiennej = tmp[0];
			z = z->znajdzZmienna(pom, nazwaZmiennej, zmienne);
			if(pom == 1)	{
				wyniki.push(*z);
			}
			kolejka.pop();
		}
		else if(isdigit(tmp[0]) != 0)	{
			i = 0;
			while(isdigit(tmp[i]) != 0)	{
				i++;
			}
			if(tmp[i] == 'i')	{
				liczba = new char[i + 1];
				k = 0;
				for(j = 0; j < i; j++)	{
					liczba[j] = tmp[k];
					k++;
				}
				tmpD = strtod(liczba, NULL);
				z = new liczbyZespolone(0.0, tmpD, '-');
			}
			else	{
				tmpD = strtod(tmp, NULL);
				z = new liczbyZespolone(tmpD, 0.0, '-');
			}
			wyniki.push(*z);
			kolejka.pop();
		}
		else if(isdigit(tmp[0]) == 0)	{
			if(wyniki.empty() == false)	{
				a = wyniki.top();
				wyniki.pop();
			}
			if(wyniki.empty() == false)	{
				b = wyniki.top();
				wyniki.pop();
			}
			switch(tmp[0])	{
				//Dodawanie: b + a 
				case '+':	{	
					wyniki.push(b + a);
					break;
				}
				//Odejmowanie:
				case '-':	{
					wyniki.push(b - a);
					break;
				}
				//Mnozenie:
				case '*':	{
					wyniki.push(b * a);
					break;
				}
				//Dzielenie:
				case '/':	{
					wyniki.push(b / a);
					break;
				}
			}
			kolejka.pop();
		}
	}
}
