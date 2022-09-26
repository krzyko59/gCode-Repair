#ifndef options_hpp
#define options_hpp

#include <iostream>
#include <cstring>
#include <conio.h>//_getch
#include<limits>//cin.ignore(numeric_limits<streamsize>::max(), '\n');
#include<fstream>//wczytywanie plikow
#include<cstdlib>
//generowanie kola bevel
#include <math.h>
#include <cmath>
//data
#include <windows.h>
#include <winbase.h>
#include "functions.h"
#include "console_log.h"

using std::string;
enum version
{
	//wersja programu
	vMAJOR = 0,
	//wsp�lne oznaczenie wszystkich wersji programu bazuj�cych na tych samych za�o�eniach, mechanizmach
	vMINIOR = 0,
	//oznacza si� kolejne etapy rozwoju programu w ramach tej samej koncepcji (wersji major). 
	//Zmienia si� razem z zaimplementowaniem nowej funkcji, zmian� jakiej� istniej�cej
	vRELEASE = 9,
	//m�wi, kt�rym wydaniem w ramach wersji minor jest dana paczka programu
};
bool option_1(string line[], unsigned short& line_amout, Console& console);
bool option_4(string line[], unsigned short& line_amout, Console& console);

#endif