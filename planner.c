/*
* Name : planner.c 
* 
* Call relevant functions related to planner
*/

#include "common.h"
#include "planner.h"
#include <time.h>
#include "color.h"

/*
 * windows -> #include <windows.h> 
 * HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
 * SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); 
 * printf("TEXT\n"); 
 */
 //define for coloring (Mac)
/*
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
*/

void setAlarm(int minutes) {
    printf("Alarm set for %d minutes.\n", minutes);
    //sleep(minutes * 60);
    printf("\nAlarm!\n");
}

void addTaskToFile(struct Task task, const char* filename) {
    FILE* fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(fp, "%d %d %d %d %d %s\n", task.priority, task.month, task.day, task.hour, task.minute, task.description);

    fclose(fp);
}

void loadTasksFromFile(struct Task tasks[], int* taskCount, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No tasks found.\n");
        return;
    }

    *taskCount = 0;
    while (fscanf(fp, "%d %d %d %d %d %[^\n]", &tasks[*taskCount].priority, &tasks[*taskCount].month, &tasks[*taskCount].day, &tasks[*taskCount].hour, &tasks[*taskCount].minute, tasks[*taskCount].description) == 6) {
        (*taskCount)++;
        if (*taskCount >= MAX_TASKS) {
            printf("Too many tasks. Increase MAX_TASKS.\n");
            break;
        }
    }

    fclose(fp);
}

void viewTasksByPriority(struct Task tasks[], int taskCount) {
    int found = 0;

    // Sort by deadline and priority
    qsort(tasks, taskCount, sizeof(struct Task), compareTasks);

    printf("==================== <To Do List> ====================\n");
    printf("                    View All Tasks\n\n");
    //Print sorted tasksOnDate
    for (int i = 0; i < taskCount; i++) {
        printf("[%d] Priority %d at %02d/%02d %02d:%02d: %s\n", i + 1, tasks[i].priority, tasks[i].month, tasks[i].day, tasks[i].hour, tasks[i].minute, tasks[i].description);
        found = 1;
    }

    if (!found) {
        printf("No tasks found.\n");
    }
    printf("\n======================================================\n\n");
}

void print_month(struct Task tasks[], int taskCount, int year, int month)
{
    // Array to hold the number of days in each month (considering leap years for February) (?ㅻ뀈 ?ы븿)
    int days_in_month[] = { 31, 28 + (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Getting the day of the week for the first day of the month
    struct tm timeinfo = { 0 };
    timeinfo.tm_year = year - 1900; // Years since 1900
    timeinfo.tm_mon = month - 1;    // Months start from 0
    timeinfo.tm_mday = 1;           // First day of the month
    mktime(&timeinfo);              // Normalize time

    int start_day = timeinfo.tm_wday; // Day of the week (0 - Sunday, 1 - Monday, ..., 6 - Saturday)

    // Printing the month and year
    printf("\n         %d / %d\n\n", month, year);
    // ANSI_COLOR_.. This is how to apply color on Mac.
    // Mac version     
    //printf(ANSI_COLOR_RED " Su  Mo  Tu  We  Th  Fr  Sa\n" ANSI_COLOR_RESET);
    
    //window version 
    setConsoleColor(RED);
    printf(" Su  Mo  Tu  We  Th  Fr  Sa\n");
    resetConsoleColor();

    // Printing spaces to align the first day of the month
    for (int i = 0; i < start_day; i++)
    {
        printf("    ");
    }

    // Printing the days of the month
    for (int day = 1; day <= days_in_month[month - 1]; day++)
    {
        if (isTaskDay(tasks, taskCount, year, month, day)) {
            // If it is a day with a task, the date is displayed in green.
            //Mac version
            //printf(ANSI_COLOR_GREEN "%3d" ANSI_COLOR_RESET, day);
        
            //window version
            setConsoleColor(GREEN);
            printf("%3d", day);
            resetConsoleColor();
        }
        else {
            printf("%3d", day);
        }
        if ((start_day + day) % 7 == 0 || day == days_in_month[month - 1])
        {
            printf("\n");
        }
        else
        {
            printf(" ");
        }
    }
}

int isTaskDay(struct Task tasks[], int taskCount, int year, int month, int day) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].month == month && tasks[i].day == day) {
            return 1;
        }
    }
    return 0;
}

int compareTasks(const void* a, const void* b) {
    struct Task* taskA = (struct Task*)a;
    struct Task* taskB = (struct Task*)b;

    // month comparison
    if (taskA->month < taskB->month) {
        return -1;
    }
    else if (taskA->month > taskB->month) {
        return 1;
    }
    else { // Compare days if months are the same
        if (taskA->day < taskB->day) {
            return -1;
        }
        else if (taskA->day > taskB->day) {
            return 1;
        }
        else { // Compare time if the day is the same
            if (taskA->hour < taskB->hour) {
                return -1;
            }
            else if (taskA->hour > taskB->hour) {
                return 1;
            }
            else { // Compare priorities if times are the same
                if (taskA->priority > taskB->priority) {
                    return -1;
                }
                else if (taskA->priority < taskB->priority) {
                    return 1;
                }
                else {
                    return 0;
                }
            }
        }
    }
}

void viewTasksByDate(struct Task tasks[], int taskCount, int searchMonth, int searchDay) {
    printf("\nTasks on %02d/%02d sorted by deadline and priority:\n", searchMonth, searchDay);
    int found = 1;

    struct Task tasksOnDate[MAX_TASKS]; // Array containing tasks for that date
    int countOnDate = 0;

    // Copy tasks belonging to that date to tasksOnDate
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].month == searchMonth && tasks[i].day == searchDay) {
            tasksOnDate[countOnDate++] = tasks[i];
        }
    }

    // Sort by deadline and priority
    qsort(tasksOnDate, countOnDate, sizeof(struct Task), compareTasks);

    printf("==================== <To Do List> ====================\n\n");
    // Print sorted tasksOnDate
    for (int i = 0; i < countOnDate; i++) {
        printf("[%d] Priority %d at %02d/%02d %02d:%02d: %s\n", i + 1, tasksOnDate[i].priority, tasksOnDate[i].month, tasksOnDate[i].day, tasksOnDate[i].hour, tasksOnDate[i].minute, tasksOnDate[i].description);
        found = 1;
    }

    if (!found) {
        printf("No tasks found on %02d/%02d.\n", searchMonth, searchDay);
    }
    printf("\n======================================================\n\n");
}

void deleteTaskByDateTime(struct Task tasks[], int* taskCount, const char* filename) {
    int deleteMonth, deleteDay, deleteHour, deleteMinute, indexToDelete = -1;
    struct Task temp;
    printf("Enter the month, day, hour and minute of the task to delete (MM DD HH mm): ");
    scanf("%d %d %d %d", &deleteMonth, &deleteDay, &deleteHour, &deleteMinute);

    for (int i = 0; i < *taskCount; i++) {
        if (tasks[i].month == deleteMonth && tasks[i].day == deleteDay && tasks[i].hour == deleteHour && tasks[i].minute == deleteMinute) {
            indexToDelete = i;
            temp = tasks[i];
            break;
        }
    }

    if (indexToDelete != -1) {
        // When a matching schedule is found, delete the schedule and update the file
        for (int i = indexToDelete; i < *taskCount - 1; i++) {
            tasks[i] = tasks[i + 1];
        }

        (*taskCount)--;
        // Rewrite updated schedule to file
        FILE* fp = fopen(filename, "w");
        if (fp == NULL) {
            printf("Error opening file!\n");
            return;
        }

        
        for (int i = 0; i < *taskCount; i++) {
            fprintf(fp, "%d %d %d %d %d %s\n", tasks[i].priority, tasks[i].month, tasks[i].day, tasks[i].hour, tasks[i].minute, tasks[i].description);
        }

        fclose(fp);

        printf("Task deleted successfully! (Desc : %s)\n", temp.description);
    }
    else {
        printf("Task with given date and time not found!\n");
    }
}


int planner_main() {
    int choice;
    struct Task tasks[MAX_TASKS];
    int taskCount = 0;

    time_t t = time(NULL);
    struct tm* current_time = localtime(&t);

    int year = current_time->tm_year + 1900;
    int month = current_time->tm_mon + 1;

    int searchMonth, searchDay;

    loadTasksFromFile(tasks, &taskCount, "tasks.txt");

    do {
        printf("\n1. Add Task\n");
        printf("2. Delete Task\n");
        printf("3. View Tasks by sorted order\n");
        printf("4. View Calendar (Current Month)\n");
        printf("5. View tasks by date\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1: {
            struct Task task;

            printf("Enter task priority (1-5): ");
            scanf("%d", &task.priority);

            if (task.priority < 1 || task.priority > 5) {
                printf("Invalid priority. Priority should be between 1 and 5.\n");
                continue;
            }

            printf("Enter task month: ");
            scanf("%d", &task.month);

            printf("Enter task day: ");
            scanf("%d", &task.day);

            printf("Enter task hour: ");
            scanf("%d", &task.hour);

            printf("Enter task minute: ");
            scanf("%d", &task.minute);

            printf("Enter task description: ");
            scanf(" %[^\n]", task.description);

            addTaskToFile(task, "tasks.txt");
            tasks[taskCount++] = task;

            printf("Task added successfully!\n");
            break;
        }
        case 2: {
            deleteTaskByDateTime(tasks, &taskCount, "tasks.txt");
            break;
        }
        case 3:
            viewTasksByPriority(tasks, taskCount);
            break;
        case 4:
            // viewTasksByTime(tasks, taskCount);
            print_month(tasks, taskCount, year, month);
            break;
        case 5:
            printf("Enter the month and day to view tasks (MM DD): ");
            scanf("%d %d", &searchMonth, &searchDay);
            viewTasksByDate(tasks, taskCount, searchMonth, searchDay);
            break;
        case 6:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

/*end of file*/