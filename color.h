/*
* Name : color.h
* Last modified : 23-12-01
*
* Function declaration for color.c (windows)
*/

#ifndef _COLOR_H_
#define _COLOR_H_

#include <windows.h>

// Rainbow colors
#define RED     12
#define ORANGE  14
#define YELLOW  6
#define GREEN   2
#define BLUE    9
#define INDIGO  1
#define VIOLET  13

void setConsoleColor(int color);
void setConsoleBackgroundColor(int color);
void resetConsoleColor();


#endif // _COLOR_H_

