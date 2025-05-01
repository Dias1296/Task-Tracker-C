#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "utils.h"

int main()
{
    int choice;

    loadTasksFromFile();

    while (1) //Infinite loop for the main menu
    {
        showMenu();
        printf("Enter your choice: \n");
        scanf_s("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                toggleTaskAsDone();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                editTaskTitle();
                break;
            case 6:
                showTaskSummary();
                break;
            case 7:
                searchTasksByKeyword();
                break;
            case 0:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice.");
        }

        printf("\nPress Enter to continue...\n");
        getchar();
        system("cls"); // Clear the console screen (Windows only)
    }

    return 0;
}