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
#include "console_log.h"
#include "options.h"

using namespace std;

void show_separation();
void show_options_to_select(short used_options[],  Console& console);
void show_program_info(Console& console);
void show_blad(string text, Console& console);
void show_sukces(string text, Console& console);
char load_options_to_select(short used_options[], Console& console);
void remove_quote(string& file_path);
void what_file_to_load(string& file_path, int argc, char** argv, Console& console);
string to_uppercase(string text);
bool is_ncp(string& file_path, Console& console);
bool load_file(string& file_path, ifstream& loaded_file, string line[], unsigned short& line_amout, Console& console);
void remove_N_numbering(string line[], unsigned short& line_amout, Console& console);
void add_N_numbering(string line[], unsigned short& line_amout);
void DEBUG_show_lines(string line[], unsigned short& line_amout);
bool save_file(string& file_path, string line[], unsigned short& line_amout, Console& console);
void end_program();
void insert_line(int shift_amout, int from_line, string line[], unsigned short& line_amout);
void remove_line(int shift_amout, int from_line, string line[], unsigned short& line_amout);
void add_gcode_info(short used_options[], string line[], unsigned short& line_amout);
int rfind_line(string phrase, int from, string line[]);
int find_line(string phrase, int from, string line[], unsigned short& line_amout);
void phrase_replace(string& text, string from, string to);
void normalize_g(string line[], unsigned short& line_amout);
string take_data(string text, string data_param);
double round_two(double data);