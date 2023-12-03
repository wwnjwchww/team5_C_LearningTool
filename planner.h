/*
* planner.h
*
* planner.c related function declarations and structures
*/
#ifndef _PLANNER_H_
#define _PLANNER_H_

#define MAX_TASKS 100
struct Task {
	int priority;
	int month;
	int day;
	int hour;
	int minute;
	char description[255];
};
void setAlarm(int minutes);
void addTaskToFile(struct Task task, const char* filename);
void loadTasksFromFile(struct Task tasks[], int* taskCount, const char* filename);
void viewTasksByPriority(struct Task tasks[], int taskCount);
void viewTasksByTime(struct Task tasks[], int taskCount);
void print_month(struct Task tasks[], int taskCount, int year, int month);
int isTaskDay(struct Task tasks[], int taskCount, int year, int month, int day);
int compareTasks(const void* a, const void* b);
void viewTasksByDate(struct Task tasks[], int taskCount, int searchMonth, int searchDay);
void deleteTaskByDateTime(struct Task tasks[], int* taskCount, const char* filename);
int planner_main();

#endif // !_PLANNER_H_
/*end of file*/
