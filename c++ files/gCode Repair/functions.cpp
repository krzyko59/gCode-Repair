#include "functions.h"

char load_options_to_select(short used_options[], Console& console)
{
    char choice = _getch();
    bool bad_choice = false;
    while (choice < 48 || (choice > 53 && choice != 57))//'0'-48 '5'-53 '9'=57
    {
        console.add_console_log("Nie ma takiej opcji do wybrania", console_colors(C_WHITE));
        console.show_console_log();
        console.show_options_to_select(used_options);
        choice = _getch();
    }
    return choice;
}
void remove_quote(string& file_path)
{
    if (file_path.find("\"", 0) == 0 && file_path.rfind("\"", file_path.size()) == file_path.size() - 1)
    {
        string text;
        text.insert(0, file_path, 1, file_path.size() - 2);
        file_path.clear();
        file_path.insert(0, text);
    }
}
string to_uppercase(string text)
{
    int i = text.size();
    while (i--)
        if (text[i] > 96 && text[i] < 122)
            text[i] = (text[i] - 32);
    return text;
}
bool is_ncp(string& file_path, Console& console)
{
    string text = to_uppercase(file_path);
    if (text.rfind(".NCP", text.size()) == text.size() - 4)
        return true;
    console.add_console_log("Plik ktory probujesz wczytac nie ma rozszerzenia * .NCP", console_colors(C_RED));
    return false;
}
bool load_file(string& file_path, ifstream& loaded_file, string line[], unsigned short& line_amout, Console& console)
{
    //TODO: load_file: problem przy wczytywaniu pliku  z '—' ( EM DASH ) w nazwie.
    loaded_file.open(file_path);
    if (!loaded_file.good())
    {
        console.add_console_log("Odczyt pliku byl nie mozliwy : " + file_path, console_colors(C_RED));
        return false;
    }
    line_amout = 0;
    string line_temp;
    while (!loaded_file.eof())
    {
        getline(loaded_file, line_temp);
        if (line_temp == "")
            continue;
        line[line_amout].insert(0, line_temp);
        line_amout++;
    }
    loaded_file.close();
    console.add_console_log("Udalo sie wczytac plik : " + file_path, console_colors(C_GREEN));
    return true;
}
void remove_N_numbering(string line[], unsigned short& line_amout, Console& console)
{
    for (unsigned short i = 0; i < line_amout; i++)
    {
        if (line[i] == "")
            continue;
        if ((line[i].find("\"", 0) == string::npos && line[i].find("N", 0) != 0) &&
            (line[i].find("N", 1) != string::npos && //brak wiecej N
                line[i].find("N", 1) < line[i].find("\"", 1)))
        {
            console.add_console_log("Zla numeracja N lini: " + to_string(i), console_colors(C_RED));
            return;
        }
        if (line[i].find("\"", 0) != string::npos && line[i].find("N", 0) != 0)
            continue;
        short to_position;
        to_position = line[i].find(" ", 0) + 1;
        line[i].erase(0, to_position);
    }
}
void add_N_numbering(string line[], unsigned short& line_amout)
{
    int skipped_lines = 0;
    for (unsigned short i = 0; i < line_amout; i++)
    {
        if (line[i].find("\"", 0) == string::npos)
            line[i].insert(0, "N" + to_string(i + 1 - skipped_lines) + "0 ");
        else
        {
            for (int j = 0; j < line[i].find("\"", 0); j++)
            {
                if (line[i].at(j) != 32)
                {
                    line[i].insert(0, "N" + to_string(i + 1 - skipped_lines) + "0 ");
                    break;
                }
                if ((j + 1) == line[i].find("\"", 0)) skipped_lines++;
            }
        }
    }
}
void DEBUG_show_lines(string line[], unsigned short& line_amout)
{
    for (unsigned short i = 0; i < line_amout; i++)
        cout << i << " | " << line[i] << endl;
}
bool is_file_exist(string FileName) 
{

    const std::filesystem::path p = FileName;
    return (std::filesystem::exists(p));
}
bool save_file(string& file_path, string line[], unsigned short& line_amout, Console& console)
{
    using std::ofstream;
    using std::ios;

    string new_file_path;
    new_file_path.insert(0, file_path, 0, file_path.rfind(".", file_path.size() - 1));
    if (is_file_exist(new_file_path + "_gCr.NCP"))
    {
        short file_version = 1;
        while (is_file_exist(new_file_path + "_gCr_V" + to_string(file_version) + ".NCP"))
            file_version++;
        new_file_path.append("_gCr_V" + to_string(file_version) + ".NCP");
    }
    else new_file_path.append("_gCr.NCP");
    ofstream file;
    file.open(new_file_path, ios::out);
    if (!file.good())
    {
        console.add_console_log("Zapis pliku byl nie mozliwy: " + new_file_path, console_colors(C_RED));
        return false;
    }
    string write_line;
    for (int i = 0; i < line_amout; i++)
    {
        write_line.clear();
        write_line.append(line[i]);
        //na koncu pliku nie dodaje nowej lini
        if (i < line_amout - 1) write_line.append("\n");
        file.write(write_line.c_str(), write_line.size());
    }
    file.close();
    console.add_console_log("Udalo sie zapisac plik : " + new_file_path, console_colors(C_GREEN));
    return true;
}
void insert_line(int shift_amout, int from_line, string line[], unsigned short& line_amout)
{
    //przesuniecie lini
    for (int i = line_amout - 1; i >= from_line; i--)
        line[i + shift_amout] = line[i];
    //czyszczenie przeniesionych lini
    for (int i = from_line; i < from_line + shift_amout; i++)
        line[i].clear();
    //zwiekszenie ilosci lini
    line_amout += shift_amout;
}
void remove_line(int shift_amout, int from_line, string line[], unsigned short& line_amout)
{
    //przesuniecie lini
    for (int i = 0; i < line_amout - from_line - shift_amout; i++)
    {
        line[from_line + i] = line[from_line + shift_amout + i];
    }
    //czyszczenie pustych lini na koncu
    for (int i = 0; i <= shift_amout; i++)
        line[line_amout - i].clear();
    //zmniejszenie ilosci lini
    line_amout -= shift_amout;
}
void add_gcode_info(short used_options[], string line[], unsigned short& line_amout)
{
    insert_line(5 + used_options[0], 0, line, line_amout);
    short add_line = 0;
    line[0] = "\"G-code edytowane za pomoc¹ programu gCode repair";
    line[1] = "\"Autor Krzysztof Kolos";
    line[2] = "\"wykonane operacje:";
    if (used_options[1])
    {
        line[3 + add_line] = "\" -Przerobiono obrys zewnetrzny na ukosowanie";
        add_line++;
    }
    if (used_options[4])
    {
        line[3 + add_line] = "\" -Obrocono glowice 3D na kat 180 stopni";
        add_line++;
    }
    SYSTEMTIME st;
    GetSystemTime(&st);
    line[3 + add_line] = "\"Data modyfikacji: " + to_string(st.wDay) + "." + to_string(st.wMonth) + "." + to_string(st.wYear);
    line[4 + add_line] = "\"Wersja oprogramowania: " + to_string(vMAJOR) + "." + to_string(vMINIOR) + "." + to_string(vRELEASE);
}
int rfind_line(string phrase, int from, string line[])
{
    for (int i = from; i > 0; i--)
        if (line[i].find(phrase, 0) != string::npos)
            return i;
    return string::npos;
}
int find_line(string phrase, int from, string line[], unsigned short& line_amout)
{
    for (int i = from; i < line_amout; i++)
        if (line[i].find(phrase, 0) != string::npos)
            return i;
    return string::npos;
}
void phrase_replace(string& text, string from, string to)
{
    if (text.find(from, 0) != string::npos)
    {
        unsigned short _position = text.find(from, 0);
        text.erase(_position, from.size());
        text.insert(_position, to);
    }
}
void normalize_g(string line[], unsigned short& line_amout)
{
    for (int i = 0; i < line_amout; i++)
    {
        phrase_replace(line[i], "G00", "G0");
        phrase_replace(line[i], "G01", "G1");
        phrase_replace(line[i], "G02", "G2");
        phrase_replace(line[i], "G03", "G3");
    }
}
string take_data(string text, string data_param)
{
    string data;
    data.insert(0, text, text.find(data_param, 0) + 1, text.find(" ", text.find(data_param, 1)) - text.find(data_param, 0) - 1);
    return data;
}
double round_two(double data)
{
    return round(data * 100) / 100;
}