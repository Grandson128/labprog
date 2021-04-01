#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "kanban.c"

Task *newTask;
Tasklist todoList;
Tasklist creationDateList;
int taskId;

void menu(int option){
    switch (option){
        case 1:
            newTask = createTask();
            insertTask(creationDateList, newTask);
            clearScreen();
            printTaskList(creationDateList);
            printf("Press ENTER to proceed\n");
            getchar();
            break;

        case 2:
            clearScreen();
            printTaskList(creationDateList);
            printf("Insert the Task ID you wish to delete\n\n   => ");
            scanf("%d", &taskId);
            deleteTask(creationDateList, taskId);
            printf("Task Eliminated\nPress ENTER to proceed\n");
            getchar();
            break;

        case 3:
            clearScreen();
            printTaskList(creationDateList);
            printf("Press ENTER to proceed\n");
            getchar();
            break;

        default:
            break;

    }
}

int main(){
    int option;
    todoList = createTaskList();
    creationDateList = createTaskList();
    while (option != 0){
        clearScreen();
        printf("O nosso projeto em C para Laboratorio de Programacao\n");

        printf("Behold the glorious menu \n\nPlease, select one of following options:\n\n");

        printf("1) Create new task\n2) Delete task\n3) List tasks\n0) Exit\n\n   => ");

        scanf("%d", &option);
        getchar();

        menu(option);
    }


    printf("I CREATE FILE NOW YES\n");

    FileExists("ola");

    CreateFile("ola");

    FileExists("ola");


    return 0;
}
