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
    return
    if (head->kolejny->kolejny==tail)
    {
        delete head->kolejny;
    }
    knot * aktualny=head->kolejny->kolejny;
    for(;;)
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
    if(head->kolejny==NULL) 
    {
		head->kolejny=new knot;
		head->kolejny->kolejny=tail;
		head->kolejny->poprzedni=head;
		tail->poprzedni=head->kolejny;
		head->kolejny->klucz=key;
        return 1;
    }
	
	knot * aktualny=head->kolejny;
	for(;;)
	{
		if(aktualny->klucz>=key)
		{
			if(aktualny->klucz==key)
				return 0;
			aktualny->poprzedni->kolejny=new knot;
			aktualny->poprzedni->kolejny->poprzedni=aktualny->poprzedni;
			aktualny->poprzedni->kolejny->kolejny=aktualny;
			aktualny->poprzedni=aktualny->poprzedni->kolejny;

			aktualny->poprzedni->klucz=key;
			return 1;
		}
		
		if(aktualny->kolejny==tail)
		{
			aktualny->kolejny=new knot;
			aktualny->kolejny->poprzedni=aktualny;
			tail->poprzedni=aktualny->kolejny;
			tail->poprzedni->kolejny=tail;
			aktualny->kolejny->klucz=key;
			return 1;
		}
		
		aktualny=aktualny->kolejny;
		
	}
}

int dict::DeleteSkladnik(int key)
{
	if(head->kolejny==tail)
		return 0;
	
	knot * aktualny=head->kolejny;
	for(;;)
	{
		if(aktualny->klucz>key)
			return 0;
		if(aktualny->klucz==key)
		{
			aktualny->poprzedni->kolejny=aktualny->kolejny;
			aktualny->kolejny->poprzedni=aktualny->poprzedni;
			delete aktualny;
			return 1; 
		}
		if(aktualny->kolejny==tail)
			return 0;

		
		aktualny=aktualny->kolejny;
	}
}

int dict::Wyszukaj(int key)
{
	if (head->kolejny==tail)
		return 0;
	knot * aktualny=head->kolejny;
	for(;;)
	{
		if (aktualny->klucz==key)
			return 1;
		if (aktualny->klucz>key)
			return 0;
		if (aktualny->kolejny==tail)
			return 0;
		aktualny=aktualny->kolejny;
	}
}

int dict::Wypisz()
{
	if(head->kolejny==tail)
		return 0; 
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

