// 01. Lista.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <time.h>
#include <Windows.h>

struct stFoobar
{
	int iFoo;
	char cBar;
	double dBaz;
};

stFoobar** losowanie(int);
void kasowanie(stFoobar**, int);
void sortowanie(stFoobar**, int);
int zliczanie_znakow(stFoobar**, int, char);
void unit_test(int, char);

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned int) time(NULL));
	unit_test(1000, 'A');
	unit_test(10000, 'B');
	unit_test(100000, 'C');
	system("pause");
	return 0;
}

void unit_test(int size, char needle)
{
	printf("Start programu. Rozmiar danych: %i. Szukana: %c.\n", size, needle);
	
	DWORD start_time = GetTickCount();

	stFoobar** foobar = losowanie(size);

	sortowanie(foobar, size);
	printf("Znaleziono %i przypadkow '%c'.\n", zliczanie_znakow(foobar, size, needle), needle);
	kasowanie(foobar, size);

	printf("Zakonczono. Czas wynkonania: %.3fs\n===\n\n", (float)(GetTickCount() - start_time) / 1000.0f);
}


stFoobar** losowanie(int size)
{
	stFoobar **foobar = new stFoobar*[size];
	for (int i = 0; i < size; i++)
	{
		foobar[i] = new stFoobar;
		foobar[i]->iFoo = rand();
		foobar[i]->cBar = rand() % 255;
		foobar[i]->dBaz = 0.0;
	}
	return foobar;
}

void kasowanie(stFoobar** foobar, int size)
{
	for (int i = 0; i < size; i++)
	{
		delete foobar[i];
	}
	delete[] foobar;
}



void sortowanie(stFoobar** tab, int wielkosc)
{
	for (int i = wielkosc; i > 1; i--)
	{
		for (int j = 0; j < i-1; j++)
		{
			if (tab[j] > tab[j+1])
			{
				stFoobar * temp = tab[j];
				tab[j] = tab[j+1];
				tab[j+1] = temp;
			}
		}
	}
}

int zliczanie_znakow(stFoobar** foobar, int size, char needle)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		count += (int)(foobar[i]->cBar == needle);
	}
	return count;
}
