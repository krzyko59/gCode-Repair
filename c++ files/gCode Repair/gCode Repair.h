// test //TODO: add_N_numbering :wstawienie numerowania N, jezeli komentarz jest po gcode
//TODO: load_file: problem przy wczytywaniu pliku  z '—' ( EM DASH ) w nazwie.
// test //TODO: remove_N_numbering: blad gdy w lini jest "koment
//TODO: DYNAMICZNE TABLICE: 1) tablica line[]; 2) tablica console_log[]
//TODO: OBROCENIE GLOWICY NA 180: pod koniec gcode zwolnienie do 1% i cofniecie o 400mm 

#ifndef gCode_Repair_h
#define gCode_Repair_h

#include <iostream>
#include <cstring>
#include <conio.h>//_getch
#include<limits>//cin.ignore(numeric_limits<streamsize>::max(), '\n');
#include<fstream>//wczytywanie plikow
#include<cstdlib>
//generowanie kola bevel
#include <cmath>
//data
#include <windows.h>
#include <winbase.h>

#include "options.h"
#include "console_log.h"
#include "functions.h"

#endif