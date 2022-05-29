#ifndef console_log_h
#define console_log_h
#include <iostream>
#include <string>
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

using namespace std;
enum console_colors
{
	C_BLUE = 1,
	C_GREEN = 10,
	C_RED = 12,
	C_WHITE = 7
};
class Console
{ 

	//console log
	string console_log[100];
	unsigned short console_color[100];
	unsigned short console_log_size;
	//
public:
	Console();
	friend void show_program_info(Console& console);
	friend void show_separation();
	void text_color(unsigned short color);
	void show_console_log(Console& console);
	void add_console_log(/*string console_log[], unsigned short& console_log_size,*/ string log, unsigned short color/*, unsigned short console_color[]*/, Console& console);
};
#endif