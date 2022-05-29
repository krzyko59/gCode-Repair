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
using std::string;

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
	void show_separation();
	void end_program();
	void show_options_to_select(short used_options[]);
	void show_program_info();
	void what_file_to_load(string& file_path, int argc, char** argv);
	void text_color(unsigned short color);
	void show_console_log();
	void add_console_log(string log, unsigned short color);
};
#endif