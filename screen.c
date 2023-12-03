#include "common.h"
#include "planner.h"
#include "screen.h"
#include "code_checker.h"
#include "bigO.h"
#include "color.h"

void showStartScreen() {
    //setConsoleBackgroundColor(0x70); // Set a custom background color
    
    setConsoleColor(BLUE);
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ \n");
   
    setConsoleColor(10);
    printf("      C Learning Program\n");
    setConsoleColor(ORANGE);
    printf("\t\t\"for beginners\"\n");
    setConsoleColor(BLUE);
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ \n");
    resetConsoleColor();

    //printf("\n=== start screen ===\n");
    setConsoleColor(3);
    printf("\n\n\t1. Planner\n");

    setConsoleColor(11);
    printf("\t2. Learning Tool\n");
    
    setConsoleColor(15);
    printf("\t3. Exit()\n\n");
    
    setConsoleColor(12);
    printf("                                 ■■ \n");
    setConsoleColor(13);
    printf("                                ■■■ \n");
    setConsoleColor(9);
    printf("                               ■■■■ \n");
    setConsoleColor(11);
    printf("                              ■■■■■ \n");
    setConsoleColor(14);
    printf("                            ■■■■■■■ \n");
    setConsoleColor(8);
    printf("                        ■■■■■■■■■■■ \n");
    setConsoleColor(6);
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ \n");

    resetConsoleColor();
}

void showPlannerScreen() {
    system("cls");
    //setConsoleBackgroundColor(0x80);
    setConsoleColor(1);
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ \n");
    setConsoleColor(3);
    printf("      \tPlanner Program\n");
    setConsoleColor(11);
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ \n");
    resetConsoleColor();

 
    planner_main();
}

void showLearningToolScreen() {
    system("cls");
    //setConsoleBackgroundColor(0x80);
    setConsoleColor(1);
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ \n");
    setConsoleColor(3);
    printf("          Learning Tool\n");
    setConsoleColor(11);
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ \n");
    resetConsoleColor();



    // Print the necessary content on the learning tool screen
    int choice;

    do {

        printf("\n1. Big-O Calculation\n");
        printf("2. Code Checker\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            bigO_main();
            break;
        }
        case 2: {
            code_checker_main();
            break;
        }
        case 3:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

}

