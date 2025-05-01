#include <stdio.h>
#include <string.h>
#include "task.h"
#include "utils.h"

Task tasks[MAX_TASKS];
int taskCount = 0;
const char* TASKS_FILE = "tasksSaveFile.txt";

void addTask() {
	if (taskCount >= MAX_TASKS) {
		printf("Task list is full.\n");
		return;
	}

	printf("Enter task title: ");
	fgets(tasks[taskCount].title, MAX_TITLE_LENGTH, stdin);
	
	//Remove trailing newline from fgets
	tasks[taskCount].title[strcspn(tasks[taskCount].title, "\n")] = '\0';
	tasks[taskCount].done = 0;

	taskCount++;
	saveTasksToFile();
	printf("Task added successfully.\n");

}

void viewTasks() {
	if (taskCount == 0) {
		printf("No tasks found\n");
		return;
	}

	printf("Your tasks:\n");
	for (int i = 0; i < taskCount; i++) {
		printf("%d. [%c] %s\n", i + 1, tasks[i].done ? 'x' : ' ', tasks[i].title);
	}
}

void deleteTask() {
	int index;
	viewTasks();

	if (taskCount == 0)
		return;

	printf("Enter task number to delete: \n");
	scanf_s("%d", &index);
	while (getchar() != '\n'); // Flush input

	if (index < 1 || index > taskCount) {
		printf("Invalid task number.\n");
		return;
	}

	//Shift tasks to fill the gap
	for (int i = index - 1; i < taskCount - 1; i++) {
		tasks[i] = tasks[i + 1];
	}

	taskCount--;
	saveTasksToFile();
	printf("Task deleted.\n");
}

void editTaskTitle() {
	int index;
	char newTitle[MAX_TITLE_LENGTH];

	viewTasks();

	printf("Enter the task number you want to edit: \n");
	scanf_s("%d", &index);
	while (getchar() != '\n');

	if (index <= 0 || index > taskCount) {
		printf("Invalid task number. \n");
		return;
	}

	printf("Enter the new title for the task: ");
	fgets(newTitle, MAX_TITLE_LENGTH, stdin);

	//Remove the trailing newline
	size_t len = strlen(newTitle);
	if (len > 0 && newTitle[len - 1] == '\n') {
		newTitle[len - 1] = '\0';
	}

	//Update the title
	strcpy_s(tasks[index - 1].title, MAX_TITLE_LENGTH, newTitle);

	saveTasksToFile();
	printf("Task updated successfully. \n");
}

void toggleTaskAsDone() {
	int index;

	viewTasks();
	printf("Enter task number to toggle as done: \n");
	scanf_s("%d", &index);

	while (getchar() != '\n'); // Flush input

	if (index < 0 || index > taskCount) {
		printf("Invalid task index\n");
		return;
	}

	if (tasks[index - 1].done == 0){
		tasks[index - 1].done = 1;
	}
	else {
		tasks[index - 1].done = 0;
	}

	saveTasksToFile();
	printf("Task '%s' marked as done.\n", tasks[index - 1].title);
}

void showTaskSummary() {
	int doneCount = 0;
	int notDoneCount = 0;

	for (int i = 0; i < taskCount; i++) {
		if (tasks[i].done) {
			doneCount++;
		}
		else {
			notDoneCount++;
		}
	}

	printf("======== Task Summary =======\n");
	printf("Total tasks     : %d\n", taskCount);
	printf("Completed tasks : %d\n", doneCount);
	printf("Pending tasks   : %d\n", notDoneCount);
}

void searchTasksByKeyword() {
	char keyword[MAX_TITLE_LENGTH];
	char loweredTitle[MAX_TITLE_LENGTH];
	char loweredKeyword[MAX_TITLE_LENGTH];
	int found = 0;

	printf("Enter a keyword to search:  ");
	fgets(keyword, MAX_TITLE_LENGTH, stdin);

	//Remove trailing newline
	size_t len = strlen(keyword);
	if (len > 0 && keyword[len - 1] == '\n') {
		keyword[len - 1] = '\0';
	}

	strcpy_s(loweredKeyword, MAX_TITLE_LENGTH, keyword);
	toLowerCase(loweredKeyword);

	printf("==== = Matching Tasks =====\n");
	for (int i = 0; i < taskCount; i++) {
		strcpy_s(loweredTitle, MAX_TITLE_LENGTH, tasks[i].title);
		toLowerCase(loweredTitle); 

		if (strstr(loweredTitle, loweredKeyword) != NULL) {
			printf("%d. [%s] %s\n", i + 1, tasks[i].done ? "X" : " ", tasks[i].title);
			found = 1;
		}
	}

	if (!found) {
		printf("No matching tasks found.\n");
	}
}

void loadTasksFromFile() {
	FILE* file = fopen(TASKS_FILE, "r");
	if (file == NULL) {
		return; //Check if there is a file yet
	}

	taskCount = 0;

	while (taskCount < MAX_TASKS && fscanf_s(file, "%d;", &tasks[taskCount].done) == 1) {
		if (fgets(tasks[taskCount].title, MAX_TITLE_LENGTH, file)) {
			tasks[taskCount].title[strcspn(tasks[taskCount].title, "\n")] = '\0';
			taskCount++;
		}
	}

	fclose(file);
}

void saveTasksToFile() {
	FILE* file = fopen(TASKS_FILE, "w");
	if (file == NULL) {
		printf("Error saving tasks. \n");
		return;
	}

	for (int i = 0; i < taskCount; i++) {
		fprintf(file, "%d;%s\n", tasks[i].done, tasks[i].title);
	}

	fclose(file);
}