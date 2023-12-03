/*
* Name : color.c
* Last modified : 23-12-01
*
* Functions for coloring (windows)
*/

#include "common.h"
#include "color.h"


// Set text color using Windows API
void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Set background color using system command
void setConsoleBackgroundColor(int color) {
    char command[20];
    sprintf(command, "color %02X", color);
    system(command);
}

void resetConsoleColor() {
    setConsoleColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
}
