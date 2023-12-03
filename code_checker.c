/*
* Name : code_checker.c (ver1.0)
* Last modified : 23-11-28(Tue)
*
* Function definitions needed to check code grammar
*/

#include "common.h"
#include "code_checker.h"
#include "color.h"

// ----------- Check List ------------ //
/*
 * (line: 34, 35) fscanf, fprintf prototype modification => fprintfckeck, fscanfcheck (override)
 * (line: 182) pos = j + 1 in the keyword function; I don't know what it's used for...
 * (line: 299) In builtinfunction, the 5th value of the sync array was modified from fsanf to fscanf.
 * (line: 717, 725) When printingf in varcount function, total[6], memory[6] incorrect memory access -> removed
 */

 /*
  * main function
  *
  * - Load and read the input file
  * - Starts code inspection and displays the results of each function in the terminal.
  *
  */
int code_checker_main()
{
    system("cls");
    setConsoleColor(26);
    printf("                                                        \n");
    printf("                < Code Checker Program >                \n");
    printf("                                                        \n");
    resetConsoleColor();

    FILE* input;
    fileline str[100];
    char str1[100];
    int totallen, j, i = 0, len, found;
    input = fopen("input.txt", "r");
    if (input == NULL)
    {
        exit(1);
    }
    while (fgets(str1, 100, input) != NULL)
    {
        len = strlen(str1);        // length of a line
        found = search(str1, len); // position of comment if exists
        if (str1[0] != '\n' && found == -1)
        {
            str[i].lineno = i + 1;
            str[i].linelen = len;
            strcpy(str[i].linetext, str1);
            i++;
        }
        else if (str1[0] != '\n' && found != -1)
        {
            str[i].lineno = i + 1;
            for (j = 0; j < found; j++)
                str[i].linetext[j] = str1[j];
            str[i].linetext[found] = '\n';
            str[i].linelen = strlen(str[i].linetext);
            i++;
        }
    }
    totallen = i;
    
    printf("\n\n           OUTPUT PRINTED ON TEXT FILE \n");
    setConsoleColor(GREEN);
    printf("\t\t\t\t\t->\"output.txt\"\n\n\n");
    print(str, totallen);
    resetConsoleColor();

    setConsoleColor(31);
    printf("            1. BRACKET, PARANTHESIS Check               \n\n");
    bracket(str, totallen);
    resetConsoleColor();

    setConsoleColor(ORANGE); 
    printf("(1) KEYWORDS with LINE NUMBER\n");
    resetConsoleColor();
    keyword(str, totallen);
    // protocheck(str,totallen);
    
    setConsoleColor(ORANGE);
    printf("\n(2) TOTAL NUMBER OF BUILTIN FUNCTIONS USED\n");
    resetConsoleColor();
    builtinfunction(str, totallen);
    
    //setConsoleColor(ORANGE);
    //printf("\n(3-1) TOTAL FUNCTIONS USED INCLUDING MAIN\n");
    //resetConsoleColor();
    //function_and_prototype_count(str, totallen);

    setConsoleColor(ORANGE);
    printf("\n(3) VARIABLES WITH COUNTS\n");
    resetConsoleColor();
    varcount(str, totallen);
    
    printf("\n\n");
    setConsoleColor(31);
    printf("                  2. SYNTAX CHECK                      ");
    // printscan(str,totallen);
    resetConsoleColor();
    printf("\n\n");
    setConsoleColor(RED);
    fcheck(str, totallen);
    resetConsoleColor();

    setConsoleColor(ORANGE);
    printf("\n(1). TOTAL LINES IN PROGRAM\n");
    resetConsoleColor();
    printf("    ->\tTotal line in Program are: %d\n\n\n", totallen);

    

    return 0;
}

/*
 *print function
 * input: fileline line information, length(int)
 * output:
 *
 * - Write results to output file
 *
 */
void print(fileline str[], int len)
{
    FILE* fout;
    int i;
    fout = fopen("output.txt", "w");
    if (fout == NULL)
    { 
        printf("File open failed.");
        exit(1);
    }
    for (i = 0; i < len; i++)
    {
        fprintf(fout, "line %d [%d]: %s", str[i].lineno, str[i].linelen, str[i].linetext);
    }
}

/*
 * search function
 * input: line(char[]), length(int)
 * output: return i or -1
 *
 * - Check whether a comment exists in the line loaded as input (check whether the character '/' exists)
 * - If '/' exists in the ith position, return i, otherwise, return -1
 */
int search(char arr[], int len)
{
    int found = 0, i;
    for (i = 0; !found && i < len; i++)
    {
        if (arr[i] == '/' && arr[i + 1] == '/')
        { /// If you find the comment character
            return i;
            found = 1;
        }
    }
    if (!found)
        return -1;
}
/*
 * keyword function
 * input: fileline line information, length(int)
 * output:
 *
 * Store keyword words corresponding to sync in array a,
 * Compare these and if there is a matching keyword, the result is output along with the corresponding line number.
 *
 */
void keyword(fileline arr[], int len)
{
    char str[100], a[100];
    char sync[32][10] = { "auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof", "volatile", "do", "if", "static", "while" };
    int i, j, l;

    for (i = 0; i < len; i++)
    {
        int pos = 0, k = 0;
        strcpy(str, arr[i].linetext); // Copy input data to str array
        for (j = 0; j < arr[i].linelen; j++)
        { // Start checking the length of the string
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            {                // Separate words based on characters such as spaces, parentheses, end of string, tab, etc.
                a[k] = '\0'; // Insert termination character into array a
                for (l = 0; l < 32; l++)
                {                                                  // Compare with 32 sync array strings
                    if (strcmp(a, sync[l]) == 0)                   //if it matches
                        printf("    ->\tLine %d: %s\n", arr[i].lineno, a); // Print out the line numbers and keywords used
                }
                k = 0;
                pos = j + 1; 
            }
            else
            {                  // Unless it is a separator character (' ', '(', etc.)
                a[k] = str[j]; // Continue adding characters to array a
                k++;
            }
        }
    }
}

/*
 * bracket function
 * input: fileline line information, length(int)
 * output:
 *
 * Go through each line and inspect the text of that line
 * When { }, ( ), or [ ] is found, the number of corresponding parentheses is counted and each line number is stored in the array accordingly.
 * If there is an imbalance in parentheses, output the corresponding line number along with what type of parenthesis it is.
 * If the number of parentheses does not match, the line number and type of the imbalanced parenthesis are output.
 *
 */
void bracket(fileline arr[], int len)
{
    int* p;
    int i, j;
    p = (int*)calloc(3, sizeof(int)); // Dynamic allocation of a pointer variable that can hold 3 int type variables
    if (p == NULL) {
        printf("memory alloc fail\n");
        return;
    }
    int linea1[20], linea2[20], lineb1[20], lineb2[20], linec1[20], linec2[20], a = 0, a2 = 0, b = 0, b2 = 0, c = 0, c2 = 0;
    for (i = 0; i < len; i++)
    { // As many as the number of arr arrays (as many as len)
        for (j = 0; j < arr[i].linelen; j++)
        { // As long as the line included in the structure
            if (arr[i].linetext[j] == '{')
            {                                // If '{' exists
                *p = *p + 1;                 // Add 1 to the content value of the address currently pointed to by p.
                linea1[a++] = arr[i].lineno; // Store the corresponding line number in the linea1 array
            }
            else if (arr[i].linetext[j] == '}')
            {
                *p = *p - 1;                  // Subtract 1 from the content value of the address currently pointed to by p.
                linea2[a2++] = arr[i].lineno; // Store the corresponding line number in the linea2 array
            }
            else if (arr[i].linetext[j] == '(')
            {
                *(p + 1) = *(p + 1) + 1;     // Add the next address content value of 1 to the address currently pointed to by p.
                lineb1[b++] = arr[i].lineno; // Store the corresponding line number in the linea1 array
            }
            else if (arr[i].linetext[j] == ')')
            {
                *(p + 1) = *(p + 1) - 1;      // Subtract 1 from the content value of the address currently pointed to by p.
                lineb2[b2++] = arr[i].lineno; // Store the corresponding line number in the linea2 array
            }
            else if (arr[i].linetext[j] == '[')
            {
                *(p + 2) = *(p + 2) + 1;     // Add the next address content value of 1 to the address currently pointed to by p.
                linec1[c++] = arr[i].lineno; // Store the corresponding line number in the linec1 array
            }
            else if (arr[i].linetext[j] == ']')
            {
                *(p + 2) = *(p + 2) - 1;      // Add the next address content value of 1 to the address currently pointed to by p.
                linec2[c2++] = arr[i].lineno; // Store the corresponding line number in the linec2 array
            }
        }
    }
    while (*p > 0)
    {                                                   // If the content of the position currently pointed to by p is greater than 0
                                                        // => Applies to the case where the number of times '}' is found is less than the number of times '{' is found.
                                                        // => You can see that there are parts where the parentheses are not closed properly.
        printf("line %d: { is greater\n", linea1[--a]); // Print the corresponding line number along with the result
        *p -= 1;                                        // Decrease content 1 and check again
    }
    while (*p < 0)
    { // If the content of the position currently pointed to by p is less than 0
      // => Applies to the case where the number of times '{' is found is less than the number of times '}' is found.
      // => You can see that there are parts where the parentheses are not opened properly.
        printf("line %d: } is greater\n", linea2[--a2]);
        *p += 1; // content 1 더하고 다시 확인
    }
    while (*(p + 1) > 0)
    { // Check the address of p + 1 in the same way as above.
        printf("line %d: ( is greater\n", lineb1[--b]);
        *(p + 1) -= 1;
    }
    while (*(p + 1) < 0)
    { // Check the address of p + 1 in the same way as above.
        printf("line %d: ) is greater\n", lineb2[--b2]);
        *(p + 1) += 1;
    }
    while (*(p + 2) > 0)
    { // Check the address of p + 2 in the same way as above.
        printf("line %d: [ is greater\n", linec1[--c]);
        *(p + 2) -= 1;
    }
    while (*(p + 2) < 0)
    { // Check the address of p + 2 in the same way as above.
        printf("line %d: ] is greater\n", linec2[--c2]);
        *(p + 2) += 1;
    }
    free(p);
}

/*
 * Built-in function
 * input: fileline line information, length(int)
 * output:
 *
 * Measure how much predefined functions are used in the written code
 *
 * Navigate through each line of the file, examining the text in the line
 * Separate strings based on characters such as spaces, parentheses, NULL characters, and tabs and store them in array a[]
 * Count the total number of used built-in functions by checking if they match the function names in the built-in function array sync[][]
 * Finally output the total number of used built-in functions
 *
 */
void builtinfunction(fileline arr[], int len)
{
    char str[100], a[100];
    
    char sync[30][10] = { "printf", "scanf", "gets", "puts", "fscanf", "fprintf", "fgets", "fputs", "fputc", "fgetc", "fopen", "fclose", "feof", "fflush", "malloc", "calloc", "rand", "strcmp", "strlen", "strcpy", "strncpy", "strncmp", "tolower", "toupper", "strrev", "getch", "strcat", "strncat", "sqrt", "pow" };
    int i, j, l, total = 0;

    for (i = 0; i < len; i++)
    { // Check as many as the number of arr arrays
        int pos = 0, k = 0;
        strcpy(str, arr[i].linetext); // Copy arr line information to str array
        for (j = 0; j < arr[i].linelen; j++)
        { // Check the length of the line
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            { // If you find the string separator
                a[k] = '\0';
                for (l = 0; l < 30; l++)
                { // Check if it is a built-in function corresponding to sync
                    if (strcmp(a, sync[l]) == 0)
                        total += 1; // If it matches, perform total += 1
                }
                k = 0;
                pos = j + 1;
            }
            else
            {
                a[k] = str[j];
                k++;
            }
        }
    }
    printf("    ->\tTotal Builtin Functions: %d\n", total); // Final information output
}

/*
 *printscan function
 * input: fileline line information, size(int)
 * output:
 *
 * Find printf and scanf function calls in each line of a text file
 *
 * Examine each line of the file through a for loop
 * Ignores any space or tab characters at the beginning of each line and finds where the actual code begins.
 * Inspect the substring on that line to see if it calls printf and scanf
 * If there is printf in the line, call the printcheck() function, and if there is scanf in the line, call the scancheck() function.
 * Output a message indicating that the function exists
 *
 */
void printscan(fileline arr[], int size)
{
    int i, j, k, l, x;
    char str[100];

    for (i = 0; i < size; i++)
    {
        for (x = 0; (arr[i].linetext[x] == ' ' || arr[i].linetext[x] == '\t'); x++)
            ;            // Find where the actual code is running
        printf("%d", x); // Is it necessary to output the x value..?
        // strcpy(str,arr[i].linetext);
        for (int a = 0; a < arr[i].linelen - x; a++)
        { // Copy the rest to the str array
            str[a] = arr[i].linetext[x + a];
        }

        if (strncmp(arr[i].linetext, "printf", 6) == 0)
        {                                    // if printf exists
            printcheck(str, arr[i].linelen); // Run printcheck function
            printf("printf exist\n");
        }
        if (strncmp(arr[i].linetext, "scanf", 5) == 0)
        {
            scancheck(str, arr[i].linelen);
            printf("scanf exist\n");
        }
    }
}

/*
 * printcheck function
 * input: char array, size(int)
 * output: return 0 or 1
 *
 * Check for syntax errors in printf function
 *
 * Inspect an array of strings using a for loop
 * Increment pcount each time the format character (%) appears
 * The number of commas (,) and double quotation marks (") are also counted respectively.
 * Compare the number of format characters (%) and the number of commas (,), and if they are different (pcount != ccount), set f to 1
 * If the number of double quotes (") is not even (icount % 2 != 0), set f to 1
 * If the f value is 1, there is an error, if the f value is 0, there is an error
 *
 */
int printcheck(char arr[], int size)
{
    int pcount = 0, ccount = 0, icount = 0, f = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == '%')
            pcount++;
        if (arr[i] == ',')
            ccount++;
        if (arr[i] == '\"')
            icount++;
    }
    if (pcount != ccount)
        f = 1;
    if (icount % 2 != 0)
        f = 1;

    return f;
}

/*
 * scancheck function
 * input: char array, size(int)
 * output: return 0 or 1
 *
 * Check for syntax errors in scanf function
 *
 * Inspect an array of strings using a for loop
 * Increment pcount each time the format character (%) appears
 * The number of commas (,) and double quotation marks (") are also counted respectively.
 * Count the number of address notation characters (&), count the number of string output format characters (%s)
 * Compare the number of format characters (%) and the number of commas (,), and if they are different (pcount != ccount), set f to 1
 * If the number of double quotes (") is not even (icount % 2 != 0), set f to 1
 * If &count is not used properly, ((pcount - scount) != acount) sets f to 1.
 * If the f value is 1, there is an error, if the f value is 0, there is an error
 *
 */
int scancheck(char arr[], int size)
{
    int pcount = 0, ccount = 0, icount = 0, f = 0, acount = 0, scount = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == '%')
            pcount++;
        if (arr[i] == ',')
            ccount++;
        if (arr[i] == '\"')
            icount++;
        if (arr[i] == '&')
            acount++;
        if (arr[i] == '%' && arr[i + 1] == 's')
            scount++;
    }

    if (pcount != ccount)
        f = 1;
    if (icount % 2 != 0)
        f = 1;
    if ((pcount - scount) != acount)
        f = 1;

    return f;
}

/*
 * fprintfcheck function
 * input: char array, size(int)
 * output: return 0 or 1
 *
 * Check for syntax errors in fprintf function
 *
 * Similar to printcheck and scancheck functions
 *
 */
int fprintfcheck(char arr[], int size)
{
    int pcount = 0, ccount = 0, icount = 0, f = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == '%')
            pcount++;
        if (arr[i] == ',')
            ccount++;
        if (arr[i] == '\"')
            icount++;
    }
    if (pcount != ccount - 1)
        f = 1;
    if (icount % 2 != 0)
        f = 1;

    return f;
}

/*
 * getscheck function
 * input: char array, size(int)
 * output: return 0 or 1
 *
 * Check for syntax errors in gets function
 *
 * Similar to printcheck and scancheck functions
 *
 */
int getscheck(char arr[], int size)
{
    int f = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == '%')
            f = 1;
        if (arr[i] == ',')
            f = 1;
        if (arr[i] == '\"')
            f = 1;
        if (arr[i] == '&')
            f = 1;
        if (arr[i] == '\'')
            f = 1;
    }

    return f;
}

/*
 * putscheck function
 * input: char array, size(int)
 * output: return 0 or 1
 *
 * Check for syntax errors in the puts function
 *
 * Similar to printcheck and scancheck functions
 *
 */
int putscheck(char arr[], int size)
{
    int f = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == '%')
            f = 1;
        if (arr[i] == ',')
            f = 1;
        if (arr[i] == '\"')
            f = 1;
        if (arr[i] == '&')
            f = 1;
        if (arr[i] == '\'')
            f = 1;
    }

    return f;
}
/*
 * function_and_prototype_count function
 * input: fileline information, length(int)
 * output:
 *
 * Ability to count the number of functions and function prototypes in source code
 *
 * Check prototype number while running for loop -> output
 * Next find the main function
 * Count the number of prototypes by analyzing the lines before and after finding the main function
 * Characteristics of a prototype: It starts with a specific keyword, followed by parentheses ), followed by a semicolon (;)
 * Compares the number of found prototypes with the total number of function calls, checks and notifies if prototypes for all functions do not exist.
 *
 */
void function_and_prototype_count(fileline arr[], int len)
{
    char str[100], a[100];
    char sync[7][10] = { "int", "char", "void", "double", "float", "long", "short" };
    int i, j, l, total = 0;

    // Check the total number of functions
    
    for (i = 0; i < len; i++)
    {
        int pos = 0, k = 0;
        strcpy(str, arr[i].linetext);
        int strlength;
        strlength = arr[i].linelen;
        //	printf("---> %c\n",str[strlength-2]);
        for (j = 0; j < arr[i].linelen; j++)
        {
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            {
                a[k] = '\0';
                for (l = 0; l < 7; l++)
                {
                    if ((strcmp(a, sync[l]) == 0) && str[strlength - 2] == ')')
                        total++;
                }
                k = 0;
                pos = j + 1;
            }
            else
            {
                a[k] = str[j];
                k++;
            }
        }
    }
    printf("    ->\tTotal Functions used including main function: %d\n", total);
    
    
    int fun = 0, found = 0, m, pos = 0;
    // char a[100],str[100];
     // Check the number of prototypes with functions before the main function
    for (i = 0; i < len && !found; i++)
    {
        int k = 0;
        strcpy(str, arr[i].linetext);
        for (j = 0; j < arr[i].linelen; j++)
        {
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            {
                a[k] = '\0';
                k = 0;
            }
            else
            {
                a[k] = str[j];
                k++;
            }
            if (strcmp(a, "main") == 0)
            {
                found = 1;
                pos = i;
                break;
            }
        }
    }
    // Check the number of called functions
    fun = 0;
    for (i = 0; i < pos; i++)
    {
        int k = 0;
        strcpy(str, arr[i].linetext);
        int strlength;
        strlength = arr[i].linelen;

        for (j = 0; j < arr[i].linelen; j++)
        {
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            {
                a[k] = '\0';
                for (l = 0; l < 7; l++)
                {
                    if ((strcmp(a, sync[l]) == 0) && str[strlength - 3] == ')' && str[strlength - 2] == ';')
                        fun++;
                }
                k = 0;
                pos = j + 1;
            }
            else
            {
                a[k] = str[j];
                k++;
            }
        }
    }
    setConsoleColor(ORANGE);
    printf("\n(3-2) PROTOTYPE CHECK\n");
    resetConsoleColor();

    printf("    ->\tTotal prototypes: %d\n", fun);

    if (fun < total - 1) // If the number of prototypes is less than the number of called functions
        printf("    ->\tSome prototypes are not defined\n");
    else
        printf("    ->\tPrototypes are defined\n");
}


/*
 * varcount function
 * input: fileline information, length(int)
 * output:
 *
 * How many times variables of a specific type (int, char, long, double, float, short) are declared in the source code
 * Calculate and output the amount of memory occupied by each type of variable
 *
 * Analyze the input source code (arr[]) to check if there is a variable declaration in each line.
 * Check what type the variable is declared in and count how many times it has been declared for each type (total[])
 * Calculate the amount of memory occupied by variables of each type (memory[]), output in byte units
 *
 */

void varcount(fileline arr[], int len)
{
    char str[100], a[100];
    char sync[6][10] = { "int", "char", "long", "double", "float", "short" };
    int i, j, l, total[6] = { 0 }, memory[6] = { 0 };

    for (i = 0; i < len; i++)
    {
        int pos = 0, k = 0;
        strcpy(str, arr[i].linetext);
        int strlength;
        strlength = arr[i].linelen;

        for (j = 0; j < arr[i].linelen; j++)
        {
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            {
                a[k] = '\0';
                for (int l = 0; l < 6; l++)
                {
                    if (strcmp(a, sync[l]) == 0)
                    {
                        pos = j;
                        if ((str[strlength - 3] != ')') && (str[strlength - 2] != ')'))
                        { // If not a function
                            for (int x = pos; x < strlength; x++)
                            { // Check the number of allocated variables
                                if (str[x] == ',' || str[x] == ';')
                                    total[l]++;
                            }
                        }
                    }
                }

                k = 0;
            }
            else
            {
                a[k] = str[j];
                k++;
            }
        }
    }

    // total[6] cannot be used. It was written in printf, but modified.
    printf("    ->\tTotal int: %d\n    ->\tTotal Char: %d\n    ->\tTotal long integer: %d\n    ->\tTotal Double: %d\n    ->\tTotal float: %d\n    ->\tTotal short integer: %d\n", total[0], total[1], total[2], total[3], total[4], total[5]);
    memory[0] = total[0] * sizeof(int);
    memory[1] = total[1] * sizeof(char);
    memory[2] = total[2] * sizeof(long);
    memory[3] = total[3] * sizeof(double);
    memory[4] = total[4] * sizeof(float);
    memory[5] = total[5] * sizeof(short);
    setConsoleColor(ORANGE);
    printf("\n(4) MEMORY CONSUMED BY VARIABLES\n");
    resetConsoleColor();
    // memoey[6] cannot be used. It was written in printf, but modified.
    printf("    ->\tMemory int: %d BYTES\n    ->\tMemory Char: %d BYTES\n    ->\tMemory long integer: %d BYTES\n    ->\tMemory Double: %d BYTES\n    ->\tMemory float: %d BYTES\n    ->\tMemory short integer: %d BYTES\n", memory[0], memory[1], memory[2], memory[3], memory[4], memory[5]);
}

/*
 * fscanfcheck function
 * input: char array, size(int)
 * output: return 0 or 1
 *
 * Check for syntax errors in the fscanf function
 *
 * Similar to printcheck and scancheck functions
 *
 */
int fscanfcheck(char arr[], int size)
{
    int pcount = 0, ccount = 0, icount = 0, f = 0, acount = 0, scount = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == '%')
            pcount++;
        if (arr[i] == ',')
            ccount++;
        if (arr[i] == '\"')
            icount++;
        if (arr[i] == '&')
            acount++;
        if (arr[i] == '%' && arr[i] == 's')
            scount++;
    }

    if (pcount != ccount - 1)
        f = 1;
    if (icount % 2 != 0)
        f = 1;
    if ((pcount - scount) != acount)
        f = 1;

    return f;
}

/*
 * forcheck function
 * input: char array, size(int)
 * output: return 0 or 1
 *
 * Check for grammar errors
 *
 * Similar to printcheck and scancheck functions
 *
 */
int forcheck(char arr[], int size)
{
    int pcount = 0, qcount = 0, f = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == ';')
            pcount++;

        if (arr[i] == '\'')
            qcount++;
    }
    if (pcount != 2)
        f = 1;
    if (qcount % 2 != 0)
        f = 1;

    return f;
}

/*
 * whilecheck function
 * input: char array, size(int)
 * output: return 0 or 1
 *
 * Check for while grammar errors
 *
 * Similar to printcheck and scancheck functions
 *
 */
int whilecheck(char arr[], int size)
{
    int pcount = 0, qcount = 0, f = 0, icount = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == ';')
            f = 1;

        if (arr[i] == '\'')
            qcount++;
        if (arr[i] == '\"')
            icount++;
    }

    if (qcount % 2 != 0)
        f = 1;
    if (icount % 2 != 0)
        f = 1;

    return f;
}

/*
 *fcheck function
 * input: char array, size(int)
 * output: return 0 or 1
 *
 * Certain built-in functions (printf, scanf, gets, puts, fscanf, fprintf, for, while) in source code.
 Check if there is a problem in the part where * is used -> If there is a problem, identify the error and output the number of the line
 *
 * 1. Analyze the input source code (arr[]) to check whether built-in functions are used in each line.
 * 2. Check function for the function in the part where the built-in function is used
 * (printcheck, scancheck, getscheck, putscheck, fscanfcheck, fprintfcheck, forcheck, whilecheck)
 * to check whether there is a problem with the use of the corresponding built-in function.
 * 3. If there is a problem, an error message is output along with the line number (arr[i].lineno).
 *
 */
void fcheck(fileline arr[], int len)
{
    char str[100], a[100];
    char sync[8][10] = { "printf", "scanf", "gets", "puts", "fscanf", "fprintf", "for", "while" };
    int i, j, l, f;

    for (i = 0; i < len; i++)
    {
        int pos = 0, k = 0;
        strcpy(str, arr[i].linetext);
        for (j = 0; j < arr[i].linelen; j++)
        {
            if (str[j] == ' ' || str[j] == '(' || str[j] == '\0' || str[j] == '\t')
            {
                a[k] = '\0';
                if (strcmp(a, sync[0]) == 0)
                {
                    f = printcheck(str, arr[i].linelen);
                    if (f)
                        printf("    ->\tError in Statement; ---> line no: %d\n", arr[i].lineno);
                }
                if (strcmp(a, sync[1]) == 0)
                {

                    f = scancheck(str, arr[i].linelen);
                    if (f)
                        printf("    ->\tError in Statement : ---> line no: %d\n", arr[i].lineno);
                }
                if (strcmp(a, sync[2]) == 0)
                {

                    f = getscheck(str, arr[i].linelen);
                    if (f)
                        printf("    ->\tError in Statement : ---> line no: %d\n", arr[i].lineno);
                }

                if (strcmp(a, sync[3]) == 0)
                {

                    f = putscheck(str, arr[i].linelen);
                    if (f)
                        printf("    ->\tError in Statement : ---> line no: %d\n", arr[i].lineno);
                }
                if (strcmp(a, sync[4]) == 0)
                {

                    f = fscanfcheck(str, arr[i].linelen);
                    if (f)
                        printf("    ->\tError in Statement : ---> line no: %d\n", arr[i].lineno);
                }
                if (strcmp(a, sync[5]) == 0)
                {

                    f = fprintfcheck(str, arr[i].linelen);
                    if (f)
                        printf("    ->\tError in Statement : ---> line no: %d\n", arr[i].lineno);
                }
                if (strcmp(a, sync[6]) == 0)
                {

                    f = forcheck(str, arr[i].linelen);
                    if (f)
                        printf("    ->\tError in Statement : ---> line no: %d\n", arr[i].lineno);
                }
                if (strcmp(a, sync[7]) == 0)
                {

                    f = whilecheck(str, arr[i].linelen);
                    if (f)
                        printf("    ->\tError in Statement : ---> line no: %d\n", arr[i].lineno);
                }
                k = 0;
            }
            else
            {
                a[k] = str[j];
                k++;
            }
        }
    }
}