#ifndef TASK_H
#define TASK_H

#define MAX_TASKS 100
#define MAX_TITLE_LENGTH 100

typedef struct {
	char title[MAX_TITLE_LENGTH];
	int done;
}Task;

void addTask();
void viewTasks();
void toggleTaskAsDone();
void deleteTask();
void editTaskTitle();
void showTaskSummary();
void searchTasksByKeyword();

void saveTasksToFile();
void loadTasksFromFile();

#endif
