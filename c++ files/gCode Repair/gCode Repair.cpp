// test //TODO: add_N_numbering :wstawienie numerowania N, jezeli komentarz jest po gcode
//TODO: load_file: problem przy wczytywaniu pliku  z '—' ( EM DASH ) w nazwie.
// test //TODO: remove_N_numbering: blad gdy w lini jest "koment
//TODO: DYNAMICZNE TABLICE: 1) tablica line[]; 2) tablica console_log[]
//TODO: OBROCENIE GLOWICY NA 180: pod koniec gcode zwolnienie do 1% i cofniecie o 400mm X
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



#include "options.h"
#include "console_log.h"
#include "functions.h"


int main(int argc, char** argv)
{
    Console console;
    show_program_info(console);
    string file_path;
    ifstream loaded_file;
    string line[10000];

    unsigned short line_amout = 0;
    //wczytanie pliku, przygotowanie do obróbki
    while (true)
    {
        what_file_to_load(file_path, argc, argv, console);
        if (!is_ncp(file_path, console))
            continue;
        if (!load_file(file_path, loaded_file, line, line_amout, console))
            continue;
        remove_N_numbering(line, line_amout, console);
        normalize_g(line, line_amout);
        break;
    }
    short used_options[5] = {};
    char option;
    //edytowanie pliku
    do
    {
        console.show_console_log(console);
        show_options_to_select(used_options, console);
        option = load_options_to_select(used_options, console);
        switch (option)
        {
        case '1':   //sito
            if (option_1(line, line_amout, console))
            {
                used_options[0] += 1;
                used_options[1] = 1;
            }
            break;
        case '4':   //glowica 180
            if (option_4(line, line_amout, console))
            {
                used_options[0] += 1;
                used_options[4] = 1;
            }
            break;
        case '2':   //kompensacja
        case '3':   //wejscia i wyjscia
        case '5':   //predkosc na otworach
        case '9':   //info
            console.add_console_log(/*console.console_log, console.console_log_size,*/ "OPCJA [" + to_string(option - 48) + "] NIE DOSTEPNA!!!", console_colors(C_WHITE)/*, console.console_color*/, console);
            break;
        case '0':   //zapis i koniec
            add_N_numbering(line, line_amout);
            add_gcode_info(used_options, line, line_amout);
            save_file(file_path, line, line_amout, console);
            console.show_console_log(console);
            break;
        }
    } while (option != '0');
    end_program();
    return 0;
}