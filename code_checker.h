/*
* Name : code_checker.h (ver1.0)
* Last modified : 23-11-28(Tue)
*
* Function declaration required to check code grammar
*/

#ifndef _CODE_CHECKER_H_
#define _CODE_CHECKER_H_

typedef struct
{
    int lineno;
    int linelen;
    char linetext[100];
} fileline;


void print(fileline str[], int len);
int search(char arr[], int len);
void bracket(fileline arr[], int len);
void keyword(fileline arr[], int length);
void function_and_prototype_count(fileline arr[], int len);
// void protocheck(fileline arr[],int len);
// void functioncheck(fileline arr[],int len);
void checkkeyword(fileline arr[], int len);
void builtinfunction(fileline arr[], int len);
// void count(fileline arr[],int len);
void printscan(fileline arr[], int size);
int printcheck(char arr[], int size);
int scancheck(char arr[], int size);
void varcount(fileline arr[], int len);
int getscheck(char arr[], int size);
int putscheck(char arr[], int size);
int fprintfcheck(char arr[], int size); // Override occurs because it is set to fprintf
int fscanfcheck(char arr[], int size);  // Override occurs because it is set to fprintf 
void fcheck(fileline arr[], int len);
int forcheck(char arr[], int size);
int whilecheck(char arr[], int size);
int code_checker_main();

#endif // !_CODE_CHECKER_H_


