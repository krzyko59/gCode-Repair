#include "gCode Repair.h"

using std::string;
int main(int argc, char** argv)
{
    Console console;
    console.show_program_info();
    string file_path;
    ifstream loaded_file;
    string line[10000];


    unsigned short line_amout = 0;
    //wczytanie pliku, przygotowanie do obróbki
    while (true)
    {
        console.what_file_to_load(file_path, argc, argv);
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
        console.show_console_log();
        console.show_options_to_select(used_options);
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
            console.add_console_log("OPCJA [" + to_string(option - 48) + "] NIE DOSTEPNA!!!", console_colors(C_WHITE));
            break;
        case '0':   //zapis i koniec
            add_N_numbering(line, line_amout);
            add_gcode_info(used_options, line, line_amout);
            save_file(file_path, line, line_amout, console);
            console.show_console_log();
            break;
        }
    } while (option != '0');
    console.end_program();
    return 0;
}