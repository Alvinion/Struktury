// listav2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct knot
{
    int klucz;
    knot * kolejny;
    knot * poprzedni;
};

class dict
{
    knot * head;
    knot * tail;

    public:
    dict();
    int AddNowy(int);
	int DeleteSkladnik(int);
	int Wyszukaj(int);
	int Wypisz();
	void Losowanie(int);
	~dict();
	int Wypisz2();
};

dict::~dict()
{
    if (head->kolejny==tail)
    return;//0 skladnikow
    if (head->kolejny->kolejny==tail)
    {
        delete head->kolejny;//jest jeden skladnik w liscie
    }
    knot * aktualny=head->kolejny->kolejny;
    for(;;)//wiecej niz jeden skladnik
    {
        delete aktualny->poprzedni;
        if(aktualny->kolejny==tail)
        {
            delete aktualny;
            return;
        }
        aktualny=aktualny->kolejny;
    }

}

dict::dict()
{
    head=new knot;
    tail=new knot;
    head->kolejny=NULL;
    head->poprzedni=NULL;
    tail->kolejny=NULL;
    tail->poprzedni=NULL;
}

int dict::AddNowy(int key)
{
    if(head->kolejny==NULL) //jesli lista jest pusta
    {
		head->kolejny=new knot;
		head->kolejny->kolejny=tail;
		head->kolejny->poprzedni=head;
		tail->poprzedni=head->kolejny;
		head->kolejny->klucz=key;
        return 1;
    }
	//lista nie jest pusta
	knot * aktualny=head->kolejny;
	for(;;)//petla przerywana przez return, 1 znaczy wstawiono element, 0 nie wstawiono
	{
		if(aktualny->klucz>=key)//jesli klucz aktualnego jest wiekszy badz rowny od aktualnego, wszystkie poprzednie sa mniejsze
		{
			if(aktualny->klucz==key)
				return 0;//klucz juz jest
			//takiego klucza jeszcze nie ma i jest mniejszy od tego pod aktualny
			//wpisanie nowego klucza porzed aktualnym   VVVV
			aktualny->poprzedni->kolejny=new knot;//poprzedni wskazuje na nowy
			aktualny->poprzedni->kolejny->poprzedni=aktualny->poprzedni;//nowy wskazuje na poprzedni
			aktualny->poprzedni->kolejny->kolejny=aktualny;//nowy wskazuje na aktualnyy
			aktualny->poprzedni=aktualny->poprzedni->kolejny;//aktualny wskazuje na nowy

			aktualny->poprzedni->klucz=key;
			return 1;//wstawiono nowy klucz przed aktualnym
		}
		//nowy klucz jest wiekszy od aktualnego
		if(aktualny->kolejny==tail)//jesli zaraz za aktualnym jest koniec i do tej pory nie znaleziono wiekszego klucza
		{
			aktualny->kolejny=new knot;//aktualny wskazuje na nowy
			aktualny->kolejny->poprzedni=aktualny;//nowy wskazuje na aktualny
			tail->poprzedni=aktualny->kolejny;//tail wskazuje na nowy
			tail->poprzedni->kolejny=tail;//nowy wskazuje na tail
			aktualny->kolejny->klucz=key;
			return 1;//wstawiono nowy klucz na koniec
		}
		//nie znaleziono do tej pory wiekszego klucza, nie wiadomo czy jest jakis dalej
		aktualny=aktualny->kolejny;//nowy aktualny jest kolejnym na liscie
		//petla wraca na poczatek
	}
}

int dict::DeleteSkladnik(int key)
{
	if(head->kolejny==tail)//jesli lista jest pusta
		return 0;
	//lisa nie jest pusta
	knot * aktualny=head->kolejny;//aktualny jest pierwszym elementem listy
	for(;;)
	{
		if(aktualny->klucz>key)//jesli aktualny jest wiekszy od do usuniecia to juz nie bedzie tego co do usuniecia, lista posortowana rosnaco
			return 0;
		if(aktualny->klucz==key)//jesli znaleziono wlasciwy
		{
			aktualny->poprzedni->kolejny=aktualny->kolejny;//poprzedni wskazuje na nasteopny
			aktualny->kolejny->poprzedni=aktualny->poprzedni;//kolejny wskazuje na poprzedni
			delete aktualny;//zwolnienie pamieci zajmowanej przez aktualny element
			return 1; //znaleziono i usunieto element o zadanym kluczu
		}
		if(aktualny->kolejny==tail)//jesli kolejny to tail
			return 0;

		//do tej pory nie znaleziono wymaganego klucza do usuniecia i moze byc on gdzies dalej
		aktualny=aktualny->kolejny;
	}
}

int dict::Wyszukaj(int key)
{
	if (head->kolejny==tail)
		return 0;//jesli lisat jest pusta
	knot * aktualny=head->kolejny;
	for(;;)//1 znaleziono element 0 elementu nie znaleziono
	{
		if (aktualny->klucz==key)
			return 1;//jesli znaleziono
		if (aktualny->klucz>key)
			return 0;//klucz jest juz wiekszy od keya wiiiiiiiiiiiiiiiiiiekey juz sie nie pojawi w posortowanej liscie
		if (aktualny->kolejny==tail)
			return 0;//jesli koniec listy
		aktualny=aktualny->kolejny;//jesli key moze jeszcze sie pojawic przesuwa sie wskaznik na nastepny
	}
}

int dict::Wypisz()
{
	if(head->kolejny==tail)
		return 0; //jesli lista jest pusta
	knot * aktualny=head->kolejny;
	for(;;)
	{
		cout<<aktualny->klucz<<" ";
		if (aktualny->kolejny==tail)
			return 1;
		aktualny=aktualny->kolejny;
	}
}

int dict::Wypisz2()
{
    if(head->kolejny==tail)
    return 0;
    
    knot* aktualny=tail->poprzedni;
    for(;;)
    {
           cout<<aktualny->klucz<<" ";
           if (aktualny->poprzedni==head)
           return 1;
           aktualny=aktualny->poprzedni;
}
}

void dict::Losowanie(int Ilosc)
{
	srand( time( 0 ) );

	int Liczba;
	for (;;)
	{
		if(Ilosc==0)
			return;
		//losowanie nowej liczby
		Liczba=(( rand() % 10 ) + 0 );
		if(AddNowy(Liczba)==1)
		Ilosc--;

	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	dict Nowydict;
	Nowydict.Losowanie(5);
	Nowydict.AddNowy(1000);
	Nowydict.AddNowy(1000);
	Nowydict.AddNowy(500);
	Nowydict.AddNowy(1);
	
	Nowydict.Wypisz();
	Nowydict.DeleteSkladnik(1000);
	Nowydict.DeleteSkladnik(1000);
	Nowydict.DeleteSkladnik(1);
	Nowydict.DeleteSkladnik(500);
	cout<<""<<endl;
	Nowydict.Wypisz2();
	cout<<""<<endl;
	Nowydict.DeleteSkladnik(3);
	Nowydict.Wypisz();
	cout<<""<<endl;
	cout<<""<<endl;
	Nowydict.Wypisz2();
	cout<<endl<<endl;
    system("PAUSE");
    return 0;
}

