#include "console_log.h"
#include "functions.h"
void Console::show_separation()
{
    using std::cout;
    using std::endl;
    cout << "------------------------------" << endl;
}
void Console::end_program()
{
    cout << "Wcisnij dowolny klawisz aby zamknac program";
    _getch();
}
void Console::show_options_to_select(short used_options[])
{
    cout << "\tWpisz numer opcji programu aby wykonac operacje" << endl <<
        "\tOpcje programu:" << endl;
    if (used_options[1] == 0 && used_options[4] == 0)
        cout << "[early access]\t\t[1] Konwertowanie sita na ukosowanie obrysu zewnetrznego sita" << endl;
    this->text_color(console_colors(C_RED));
    cout << "[w planach]\t\t[2] Konwertowanie na wpalenia bez kompensacji" << endl;
    cout << "[w planach]\t\t[3] Zmiana wielkosci wpalen/wyjsc" << endl;
    this->text_color(console_colors(C_WHITE));
    if (used_options[1] == 0 && used_options[4] == 0)
    cout << "[early access]\t\t[4] Obrocenie glowicy na 180 stopni w calym programie" << endl;
    this->text_color(console_colors(C_RED));
    cout << "[w planach]\t\t[5] Zmiana predkosci palenia na krzywych (otworach)" << endl;
    //cout << "\t\t[9] Informacje o mozliwosciach programu" << endl;
    this->text_color(console_colors(C_WHITE));
    cout << "\t\t\t[0] Zapis do pliku i koniec programu" << endl;
}
void Console::show_program_info()
{
    using std::cout;
    using std::endl;
    this->text_color(console_colors(C_BLUE));
    cout <<
        "\tgCODE repair" << endl <<
        "\tWersja " << version(vMAJOR) << "." << version(vMINIOR) << "." << version(vRELEASE) << endl <<
        "\tAutor: Kolos Krzysztof (krzysztof.kolos.95@gmail.com)" << endl << endl;
    this->text_color(console_colors(C_WHITE));
}
void Console::what_file_to_load(string& file_path, int argc, char** argv)
{
    using std::getline;
    if (argc != 1 && file_path == "")
    {
        file_path = argv[1];
        return;
    }
    this->show_console_log();
    cout << "\tPodaj sciezke pliku do przetworzenia: ";
    getline(cin, file_path);
    remove_quote(file_path);
}
void Console::show_console_log()
{
    system("cls");
    this->show_program_info();
    this->show_separation();
    for (unsigned short i = 0; i < console_log_size; i++)
    {
        text_color(console_colors(C_WHITE));
        cout << "*\t";
        text_color(console_color[i]);
        cout << console_log[i] << endl;
        text_color(console_colors(C_WHITE));
    }
    this->show_separation();
}
void Console::add_console_log(string log, unsigned short color)
{
    this->show_program_info();
    console_log[console_log_size] = log;
    console_color[console_log_size++] = color;
}
void Console::text_color(unsigned short color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
Console::Console()
{
    console_log_size = 0;
}
Console::~Console()
{
}