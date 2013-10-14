// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


struct typy{

	int liczba;
	char znak;
	double liczba2;

};

typy** losuj(int _n){
	
	typy** tab= new typy*[_n];	

	for (short x=0;x<_n;x++)
	{
		tab[x]=new typy;
		tab[x]->liczba=0;
		tab[x]->znak=rand();
		tab[x]->liczba2=rand();
	}

	return(tab);
}

void kasuj(typy** tab, int _n)
{
	for(short a=0; a<_n;a++)
	{
		delete tab[a];
	}

	delete tab;

}

void sortuj(){




}


int _tmain(int argc, _TCHAR* argv[])
{
}

