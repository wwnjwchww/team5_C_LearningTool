/*
* Name : bigO.h (ver1.0)
* Last modified : 23-11-28(Tue)
*
* Declarations and variables of functions defined in bigO.c
*/

#ifndef _BIG_O_H_
#define _BIG_O_H_


// Return the maximum value in the array 'arr' using selection sort
// [Time Complexity: O(n^2)]
int bigOQuadratic();

// Check the balance of braces in the string 'c'
// Return 1 if balanced, 0 otherwise
int braceCheck(char c[250]);

// Check the balance of parentheses in the string 'c'
// Return 1 if balanced, 0 otherwise
int parenthesisCheck(char c[255]);

// If 'nested' is not 0, add a value to the 'arr' array and increment the counter
void nestedLoop();

// Read strings from a file and increment a value when a specific string is encountered
// Use the parenthesisCheck function to check the balance of parentheses, repeat until the end of the file is reached
int parenthesisCheck2(char c[255]);

// Print time complexity under various conditions
// Output different time complexities based on the result of the bigOQuadratic function and the states of various variables
void TimeComplexityPrint();

// Print space complexity under various conditions
// Output different space complexities based on the result of the bigOQuadratic function and the states of various variables
void SpaceComplexityPrint();

// Decrease the 'nested' value, increase the value of NlogN_, and assign the value to the NlogN variable
void nlogN();

// Read strings from a file and, when the "for" keyword is encountered,
// recursively analyze the content inside the curly braces and call the nlogN function if necessary
void forLoop(char* c);

// Read strings from a file and, when the "while" keyword is encountered,
// recursively analyze the content inside the curly braces
void whileLoop(char* c); // In actual implementation, nlogN verification should also occur inside the while loop

// Read strings from a file and, when the "do" keyword is encountered,
// recursively analyze the content inside the curly braces
void dowhileLoop(char* c); // In actual implementation, nlogN verification should also occur inside the while loop

// These three functions analyze the forms of "for," "while," and "do while" loops, respectively,
// and recursively analyze the content inside each loop
int bigO_main();


#endif // !_BIG_O_H_

/*end of file*/

