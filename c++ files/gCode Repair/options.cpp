#include "options.h"

bool option_1(string line[], unsigned short& line_amout, Console& console)
{
    unsigned short technology_on_position = 0;
    unsigned short technology_off_position = 0;
    //szukanie lini z "TECHNOLOGY_ON" i "TECHNOLOGY_OFF"
    for (int i = line_amout; i > 0; i--)
    {
        if (line[i].find("TECHNOLOGY_ON", 0) != string::npos && technology_on_position == 0)
            technology_on_position = i;
        if (line[i].find("TECHNOLOGY_OFF", 0) != string::npos && technology_off_position == 0)
            technology_off_position = i;
        if (technology_on_position != 0 && technology_off_position != 0) break;
    }
    //zczytywanie danych
    float diametr, middle_x, middle_y, old_x, old_y, old_i, old_j;
    double new_x, new_y, new_ij;
    old_x = old_y = old_i = old_j = 0;
    for (int i = technology_off_position - 2; i > 0; i--)
    {
        if (line[i].find("G2", 0) == string::npos && line[i].find("G3", 0) == string::npos)
            continue;
        old_x = stof(take_data(line[i - 1], "X"));
        old_y = stof(take_data(line[i - 1], "Y"));
        old_i = stof(take_data(line[i], "I"));
        old_j = stof(take_data(line[i], "J"));
        break;
    }
    //czyszczenie lini
    remove_line(technology_off_position - technology_on_position + 2, technology_on_position - 1, line, line_amout);
    //obliczanie parametrow generowanego kola
    diametr = sqrt(old_i * old_i + old_j * old_j) * 2;
    middle_x = old_x + old_i;
    middle_y = old_y + old_j;
    //korekcja odchy�u g�owicy
    float corr_diametr = 13;
    float corr_middle_x = -0.5;
    float corr_middle_y = 2;

    diametr += corr_diametr;
    middle_x += corr_middle_x;
    middle_y += corr_middle_y;

    new_ij = round_two(diametr / 1.41421356237 / 2.0);

    new_x = round_two(middle_x - new_ij);
    new_y = round_two(middle_y - new_ij);

    //generowanie kola
    insert_line(8, technology_on_position - 1, line, line_amout);
    unsigned short line_to_add = 0;
    line[technology_on_position - 1 + line_to_add++].append("BEVEL_ON");
    line[technology_on_position - 1 + line_to_add++].append("G0 X" + to_string(new_x - 20) + " Y" + to_string(new_y - 20) + " G41");
    line[technology_on_position - 1 + line_to_add++].append("TECHNOLOGY_ON");
    line[technology_on_position - 1 + line_to_add++].append("G1 X" + to_string(new_x) + " Y" + to_string(new_y) + " BEVEL(0.0)");
    line[technology_on_position - 1 + line_to_add++].append("G2 X" + to_string(new_x) + " Y" + to_string(new_y) + " I" + to_string(new_ij) + " J" + to_string(new_ij) + " BEVEL(-25.0)");
    line[technology_on_position - 1 + line_to_add++].append("TECHNOLOGY_OFF G40");
    line[technology_on_position - 1 + line_to_add++].append("BEVEL_OFF");
    if (!(corr_diametr && corr_middle_x && corr_middle_y))
        console.add_console_log("Przerobiono obrys zewnetrzny na ukosowanie", console_colors(C_GREEN));
    else
        console.add_console_log("Przerobiono obrys zewnetrzny na ukosowanie z uwzglednieniem korekcji:\n srednca: " + 
            to_string((int)corr_diametr) + " srodek os X: " + to_string((int)corr_middle_x) + " srodek os Y: " + to_string((int)corr_middle_y),
            console_colors(C_GREEN));
    return true;
}
bool option_4(string line[], unsigned short& line_amout, Console& console)
{
    //szukanie lini z "INIT"
    short init_position = find_line("INIT", 0, line, line_amout);
    if (init_position == string::npos)
    {
        console.add_console_log("Program nie posiada frazy: INIT", console_colors(C_RED));
        return false;
    }
    //szukanie lini z ostatnim "TECHNOLOGY_OFF"
    short technology_off_position = rfind_line("TECHNOLOGY_OFF", line_amout, line);
    if (technology_off_position == string::npos)
    {
        console.add_console_log("Program nie posiada frazy : TECHNOLOGY_OFF", console_colors(C_RED));
        return false;
    }
    //dodanie lini "BEVEL_ON_DIRECTAX" po lini "USE_PRESELECTED"
    insert_line(1, init_position + 1, line, line_amout);
    line[init_position + 1].append("BEVEL_ON_DIRECTAX");
    ++technology_off_position;
    //dodanie lini "BEVEL_OFF" po oststniej lini "TECHNOLOGY_OFF"
    insert_line(1, technology_off_position + 1, line, line_amout);
    line[technology_off_position + 1].append("BEVEL_OFF");
    //szukaj lini z "G0", "G1"
    for (int i = 0; i < line_amout; ++i)
    {
        if (line[i].find("G0", 0) == string::npos &&
            line[i].find("G1", 0) == string::npos &&
            line[i].find("G2", 0) == string::npos &&
            line[i].find("G3", 0) == string::npos)
        {
            continue;
        }
        //ZMIANA A<X> C<X> NA A0 C180
        short from_position = line[i].find("A", 0);
        short to_position;
        if (from_position == string::npos)
        {
            line[i].append(" A0 C180");
            continue;
        }
        else
        {
            to_position = line[i].find(" ", from_position) - 1;
            line[i].erase(from_position + 1, to_position - from_position);
            line[i].insert(from_position + 1, "0");
            from_position = line[i].find("C", 0);
            to_position = line[i].find(" ", from_position) - 1;
            if (to_position == string::npos) to_position = line[i].size();
            line[i].erase(from_position + 1, to_position - from_position);
            line[i].insert(from_position + 1, "180");
        }
    }
    console.add_console_log("Obrocono glowice na 180 stopni w calym programie", console_colors(C_GREEN));
    return true;
}