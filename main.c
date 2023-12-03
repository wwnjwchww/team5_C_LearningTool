/*
* Name : main.c 
* Last modified : 23-11-28(Tue)
*
* receives user input
*/

#include "common.h"
#include "screen.h"

enum Screen {
    START_SCREEN,
    PLANNER_SCREEN,
    LEARNING_TOOL_SCREEN
};


enum Screen currentScreen = START_SCREEN;


int main() {
    int choice;

    do {
       
        switch (currentScreen) {
        case START_SCREEN:
            showStartScreen();
            break;
        case PLANNER_SCREEN:
            showPlannerScreen();
            break;
        case LEARNING_TOOL_SCREEN:
            showLearningToolScreen();
            break;
        }

    
        printf("\n\nchoose program (1.planner 2.learning tool 3.exit) : ");
        scanf("%d", &choice);

       
        switch (choice) {
        case 1:
            currentScreen = PLANNER_SCREEN;
            break;
        case 2:
            currentScreen = LEARNING_TOOL_SCREEN;
            break;
        case 3:
            printf("bye\n");
            break;
        default:
            system("cls");
            printf("Invalid choice. Please try again.\n");
            
        }

       
    } while (choice != 3);

    return 0;
}

/*end of file*/