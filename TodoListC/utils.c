#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <ctype.h>

void showMenu() {
    printf("====== TO-DO LIST MENU ======\n");
    printf("1. Add Task\n");
    printf("2. View Tasks\n");
    printf("3. Toggle Task as Done\n");
    printf("4. Delete Task\n");
    printf("5. Edit Task\n");
    printf("6. Show Task Summary\n");
    printf("7. Search Tasks by Keyword\n");
    printf("0. Exit\n");
    printf("=============================\n");
}

void toLowerCase(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = (char)tolower(str[i]);
    }
}