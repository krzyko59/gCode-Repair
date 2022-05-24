#include "console_log.h"
#include "functions.h"

void Console::show_console_log()
{
    system("cls");
    show_program_info();
    show_separation();
    for (unsigned short i = 0; i < console_log_size; i++)
    {
        text_color(C_WHITE);
        cout << "*\t";
        text_color(console_color[i]);
        cout << console_log[i] << endl;
        text_color(C_WHITE);
    }
    show_separation();
}
void Console::add_console_log(string console_log[], unsigned short& console_log_size, string log, unsigned short color, unsigned short console_color[])
{
    show_program_info();
    console_log[console_log_size] = log;
    console_color[console_log_size] = color;
    console_log_size++;
}
void Console::text_color(unsigned short color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
Console::Console()
{
    unsigned short console_log_size = 0;
}