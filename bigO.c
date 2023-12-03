/*
* Name : bigO.c (ver1.0)
* Last modified : 23-11-28(Tue)
*
* bigO calculation 
*/

#include "common.h"
#include "color.h"
#include "bigO.h"


//Count the count to determine how long it takes
int loopCount = 0;//To check the number of for statements
int counter = 0;//arr[100] Check number
int counter2 = 0;//Check whether the loop is currently running 0=loop x 1=loop o
int max = 0;////Find max value within arr[100] //Not actually used Where used->bigOQuadratic
int arr[100];//Check the number of loops for each function, maximum 100
int nested = 0;//Check for nested loops
int equals = 0;//check '=' 
int whileCount = 0;//check while
int braceCount = 0;//check for braces
int parenthesisCount = 0;//Check parentheses
int NlogN = 0;//Save NlogN number
int NlogN_ = 0;//NlogN Check whenever variable is added++
char* f = "for";
char* w = "while";

FILE* fp;
FILE* sa;

//Save and use each function keyword
char* int_ = "int";
char* float_ = "float";
char* double_ = "double";
char* long_ = "long";
char* char_ = "char";
char* printf_ = "printf";

int spaceComplexity = 0;
int intCount = 0;
int floatCount = 0;
int doubleCount = 0;
int longCount = 0;
int charCount = 0;
int logN;

int timeMeasurement = 0;


// Find and return the maximum value in array arr using selection sort
// [Time Complexity: O(n^2)]
int bigOQuadratic()
{
    int t;
    for (int i = 0; i < counter; i++)
    {
        for (int j = 0; j < counter; j++)
        {
            if (arr[j] <= arr[i])
            {
                t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
    }


    if (arr[0] == 0)
        return 0;
    else
        return arr[0] + 1;


}

// check the balance of braces in string c
// returns 1 if balanced, 0 otherwise
int braceCheck(char c[250])
{
    braceCount = 1;
    for (int i = 0; i < strlen(c); i++)
    {
        if (c[i] == '{')
        {
            braceCount++;

        }
        else if (c[i] == '}')
        {
            braceCount--;

        }

    }
    if (braceCount == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// check the balance of parentheses in string c
// returns 1 if balanced, 0 otherwise
int parenthesisCheck(char c[255])
{
    //parenthesisCount=1;
    for (int i = 0; i < strlen(c); i++)
    {
        if (c[i] == '(')
        {
            parenthesisCount++;

        }
        else if (c[i] == ')')
        {
            parenthesisCount--;
        }

    }
    if (parenthesisCount == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// If nested value is non-zero, add value to arr array and increment counter
void nestedLoop()
{

    int i = 0;

    if (nested != 0)
    {
        arr[counter] = nested;
    }
    counter++;
}

// Repeat the process of reading a string from a file and incrementing its value when a specific string appears
// Check parenthesis balance using parenthesisCheck function, repeat until end of file is reached
int parenthesisCheck2(char c[255])
{

    while (!feof(fp))
    {


        if (strstr(c, "=") != 0)
        {
            equals++;
        }
        if (strstr(c, "*") != 0)
        {
            logN++;
        }
        if (strstr(c, "/") != 0)
        {
            logN++;
        }


        fscanf(fp, "%s", c);

        if (parenthesisCheck(c) == 1)
        {

            break;
        }
    }

    
    return 0;


}

// Output time complexity according to various conditions
// Output different time complexity depending on the result of the bigOQuadratic function and the status of various variables
void TimeComplexityPrint()
{
    if (bigOQuadratic() > 0)//Because it is judged only when it is more than n^2
        printf("\nTime Complexity: O(n^%d)", bigOQuadratic());
    else if (NlogN > 0)
        printf("\nTime Complexity: O(nlogn)");
    else if (arr[0] == 0 && logN == 0 && loopCount > 0 || whileCount > 0)
        printf("\nTime Complexity: O(n) ");
    else if (arr[0] == 0 && loopCount == 1 && whileCount == 0 && logN == 1)
        printf("\nTime Complexity: O(logn)");
    else
        printf("\nTime Complexity: O(1)");
}

// Output space complexity according to various conditions
// Outputs different space complexity depending on the result of the bigOQuadratic function and the status of various variables
void SpaceComplexityPrint()
{
    if (arr[0] != 0)
    {
        if (equals == 0) {
            printf("\nSpace Complexity: n^%d+%d", bigOQuadratic(), spaceComplexity);
        }
        else {
            printf("\nSpace Complexity: %dn^%d+%d", equals, bigOQuadratic(), spaceComplexity);
        }
    }

    else if (arr[0] == 0 || loopCount > 0 || whileCount > 0) {
        if (equals == 0) {
            printf("\nSpace Complexity: n^%d+%d", bigOQuadratic() + 1, spaceComplexity);
        }
        else {
            printf("\nSpace Complexity: %dn^%d+%d O(n^%d)", equals, bigOQuadratic() + 1, spaceComplexity, bigOQuadratic() + 1);
        }
    }

}

// Decrease the nested value and increase the NlogN_ value, then assign the value to the NlogN variable
void nlogN()
{
    nested--;
    NlogN_++;
    NlogN = NlogN_;
}


void whileLoop(char* c);

// When a string is read from a file and the "for" keyword appears,
// Recursively reanalyze the contents inside the braces, calling the nlogN function if necessary
void forLoop(char* c)
{

    while (!feof(fp))
    {

        fscanf(fp, "%s", c);


        char* p = c;
        //counter2 makes each loop run only once. It compares line by line, so if counter2=0, it means that it has not been compared yet.
        if (counter2 < 1)
        {
            counter2++;
            parenthesisCheck2(c);//Check the symbols such as =,*,/ in the for, while statement within the loop and then check with the parenthesisCheck function.
        }
        if (strstr(p, "=") != 0)
        {
            equals++;
        }
        if (strstr(p, f) != 0)//If the for loop is found again within the for loop
        {
            nested++;
            counter2 = 0;// Since a new loop was found, counter2, which is a loop check, is set back to 0.
            forLoop(c);//recursive function at that point
            if (nested == 1 && logN > 0)//If nested is 1 (multiple for statements) and logN is >0, nlogN is executed.
            {
                nlogN();
            }
            logN = 0;//logN increases when performing *,/ operations in parenthesisCheck2
        }
        if (strstr(p, w) != 0)//If a while statement is encountered, nested increases
        {
            nested++;
            counter2 = 0;
            whileLoop(c);

        }

        if (braceCheck(c) == 1)
        {
            break;
        }
    }
}

// Read the string from the file and recursively reanalyze the contents inside the braces when the "while" keyword appears.
void whileLoop(char* c)//In actual implementation, nlogN must be checked even within the while statement.
{

    while (!feof(fp))
    {

        fscanf(fp, "%s", c);

        char* p = c;
        if (counter2 < 1)//Similarly, participate in the loop only if counter2 is 0
        {
            counter2++;
            parenthesisCheck2(c);
        }
        if (strstr(p, "=") != 0)
        {
            equals++;
        }
        if (strstr(p, f) != 0)
        {
            nested++;
            counter2 = 0;
            forLoop(c);
        }
        if (strstr(p, w) != 0)
        {
            nested++;
            counter2 = 0;
            whileLoop(c);
        }

        if (braceCheck(c) == 1)
        {
            break;
        }
    }
}

//When a string is read from a file and the "do" keyword appears, the content inside the braces is recursively reanalyzed.
void dowhileLoop(char* c)//In actual implementation, nlogN must be checked even within the while statement.
{
    equals++;
    while (!feof(fp))
    {
        fscanf(fp, "%s", c);

        char* p = c;
        if (counter2 < 1)
        {
            counter2++;
            parenthesisCheck2(c);
        }
        if (strstr(p, "=") != 0)
        {
            equals++;
        }
        if (strstr(p, f) != 0)
        {
            nested++;
            forLoop(c);
        }
        if (strstr(p, "do") != 0)
        {
            nested++;
            dowhileLoop(c);
        }
        if (braceCheck(c) == 1)
        {
            break;
        }
    }
}

// The three functions analyze the form of the "for", "while", and "do while" loops, respectively.
// Role of re-analyzing the contents of the loop

int bigO_main()
{
    system("cls");
   
    setConsoleColor(28);
    printf("                                                \n");
    printf("          < Big-O Calculation Program >         \n");
    printf("                                                \n");
    resetConsoleColor();
   
    clock_t start_t, end_t;
    start_t = clock();

    //system("color b"); //=> Only works on window
    setConsoleColor(11);

    int i = 0;
    int konum;
    char c[255];
    fp = fopen("distinct_subsequences.c", "r+");

    if (fp == NULL)
    {
        printf("File could not be opened");
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s", c);

            char* p = c;

            if (strstr(p, f) != 0)
            {
                loopCount++;
                forLoop(c);
                nestedLoop();
                nested = 0;
            }
            if (strstr(p, "do") != 0)
            {
                dowhileLoop(c);
                nestedLoop();
                nested = 0;
            }
            if (strstr(p, w) != 0)
            {
                whileCount++;
                whileLoop(c);
                nestedLoop();
                nested = 0;
            }
        }
        TimeComplexityPrint();
        fclose(fp);
    }

    char a[255];
    char b[255];
    fp = fopen("distinct_subsequences.c", "r+");

    if (fp == NULL)
    {
        printf("File could not be opened\n");
    }
    else
    {
        while (!feof(fp))
        {
            fscanf(fp, "%s", a);

            char* p2 = a;

            if (strstr(p2, int_) != 0)
            {
                if (strstr(p2, printf_) == 0)//?
                {
                    intCount++;

                    fscanf(fp, "%s", b);

                    if (strstr(b, "main") != 0)
                    {
                        intCount--;
                    }
                }
            }
            if (strstr(p2, float_) != 0)
            {
                spaceComplexity = spaceComplexity + sizeof(float);
                floatCount++;
            }
            if (strstr(p2, double_) != 0)
            {
                spaceComplexity = spaceComplexity + sizeof(double);
                doubleCount++;
            }
            if (strstr(p2, long_) != 0)
            {
                spaceComplexity = spaceComplexity + sizeof(long);
                longCount++;
            }
            if (strstr(p2, char_) != 0)
            {
                spaceComplexity = spaceComplexity + sizeof(char);
                charCount++;
            }
        }

        spaceComplexity = spaceComplexity + intCount * sizeof(int);
        //SpaceComplexityPrint();
        fclose(fp);
    }

    //start_t = clock();
    //system("gcc test2 -o hamiltonian\n");
    end_t = clock();

    printf("\nExecution Time of the Code is %f seconds.\n", (double)(end_t - start_t) / CLOCKS_PER_SEC);
    resetConsoleColor();
    return 0;
}

// ==========<<<<<Program analysis details>>>>>==========

/*
=====Repeat statement analysis and time complexity calculation=====
 1. Recursively analyze the contents of each loop through the forLoop, whileLoop, and dowhileLoop functions
 2. Calculate the depth of nested loop statements by calling the nestedLoop function
 3. Print the time complexity by calling the TimeComplexityPrint function.
*/

/*
=====Variable and memory space analysis=====
 1. Find and collect keywords related to variable declaration and memory allocation in the file.
 2. Calculate memory usage according to each data type and calculate space complexity by counting the number of variables.
 3. Print the space complexity by calling the SpaceComplexityPrint function.
*/

/*
=====Measure code execution time=====
1. Measure code compilation and execution time
2. Use the clock function to record the start time and end time and output the execution time.
*/



// ==========<<<<<Program Output>>>>>==========
// 1. Time complexity & space complexity
// 2. Code compilation & execution time

// ==========<<<<<Program notes>>>>>==========
// 1. Open the file using the fopen function, and output an error message if it cannot be opened.
// 2. Close the file using the fclose function.
// 3. When running the program, change the screen color to blue (system("color b")).