#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "kanban.c"

Task *newTask;
Tasklist todoList;
Tasklist doingList;
Tasklist doneList;
Tasklist creationDateList;
int taskId;

void menu(int option){
    switch (option){
        case 1:
            newTask = createTask();
            insertTask(creationDateList, newTask);
            insertTodoTask(todoList, newTask);
            clearScreen();
            printTaskList(creationDateList);
            printf("Press ENTER to proceed\n");
            getchar();
            break;

        case 2:
            clearScreen();
            printTaskList(creationDateList);
            if(creationDateList->next != NULL){
                printf("Insert the Task ID you wish to delete\n\n   => ");
                scanf("%d", &taskId);
                deleteTask(creationDateList, taskId);
                if (todoList->next != NULL) deleteTask(todoList, taskId);
                if (doingList->next != NULL) deleteTask(doingList, taskId);
                if (doneList->next != NULL) deleteTask(doneList, taskId);
                printf("\nTask Eliminated\nReturning to main menu...\n");
                sleep(3);
            }
            else{
                printf("No tasks to eliminate\nReturning to main menu...\n");
                sleep(3);
            }
            break;

        case 3:
            clearScreen();
            printTaskList(creationDateList);
            printf("Press ENTER to proceed\n");
            getchar();
            break;
        case 4:
            //todo para doing
            clearScreen();
            if (emptyTaskList(todoList) == 0){
                printTaskList(todoList);
                printf("Insert the task ID you want to transfer to Doing\n\n   => ");
                scanf("%d", &taskId);
                assignTodoDoing(todoList, doingList, taskId);
            }
            else {
                printf("Lista vazia\n\nNo tasks on the To Do list\nReturning to main menu...\n");
                sleep(3);
            }
            break;
        case 5:
            //doing para done
            clearScreen();
            if (emptyTaskList(doingList) == 0){
                printTaskList(doingList);
                printf("Insert the task ID you want to transfer to Done\n\n   => ");
                scanf("%d", &taskId);
                assignDoingDone(doingList, doneList, taskId);
            }
            else {
                printf("Lista vazia\n\nNo tasks on the Doing list\nReturning to main menu...\n");
                sleep(3);
            }
            break;
        case 6:
            clearScreen();
            printTaskList(doingList);
            if(doingList->next != NULL){
                printf("Insert the task ID you want to change admin\n\n   => ");
                scanf("%d", &taskId);
                if(taskIn(doingList,taskId) == 1){
                    changePerson(creationDateList, taskId);
                    printf("Admin changed\nReturning to main menu...\n");
                }
                else{
                    printf("No tasks on the Doing list\nReturning to main menu...\n");
                }
            }
            sleep(100);
            break;
        case 10:
            clearScreen();
            printTaskList(todoList);
            printf("Press ENTER to proceed\n");
            getchar();
            break;
        case 11:
            clearScreen();
            printTaskList(doingList);
            printf("Press ENTER to proceed\n");
            getchar();
            break;
        case 12:
            clearScreen();
            printTaskList(doneList);
            printf("Press ENTER to proceed\n");
            getchar();
            break;
        default:
            break;
    }
}

int main(){
    int option;
    int flag=0;
    int contagem=0;
    todoList = createTaskList();
    creationDateList = createTaskList();
    doingList = createTaskList();
    doneList = createTaskList();

    if(!(FileExists("data"))){
        CreateFile("data");
    }

    /*while(flag==0){
        Task *new = readFiles("data",contagem,flag);
        //insert new
        //contagem++;
    }*/

    while (option != 0){
        clearScreen();
        printf("O nosso projeto em C para Laboratorio de Programacao\n");

        printf("Behold the glorious menu \n\nPlease, select one of following options:\n\n");

        printf("1) Create new task\n2) Delete task\n3) List tasks\n4) Start Task\n5) End Task\n6) Change Doing task admin\n10) List Todo\n11) List Doing\n12) List Done\n\n0) Exit\n\n   => ");

        scanf("%d", &option);
        getchar();

        menu(option);
    }

    saveInFile("data", creationDateList);

    clearScreen();
    return 0;
}
