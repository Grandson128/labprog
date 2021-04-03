#include <stdio.h>
#include <stdlib.h>

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
            printTaskList(creationDateList);
            getchar();
            break;
        case 2:
            printf("Identificador da tarefa a eliminar\n");
            scanf("%d", &taskId);
            deleteTask(creationDateList, taskId);
             break;
        case 3:
            printTaskList(creationDateList);
            getchar();
            break;
        case 4:
            //todo para doing
            if (emptyTaskList(todoList) == 0){
                printTaskList(todoList);
                printf("Identificador da tarefa\n");
                scanf("%d", &taskId);
                assignTodoDoing(todoList, doingList, taskId);
            }else{
                printf("Lista vazia\n");
                getchar();
            }
            break;
        case 5:
            //doing para done
            if (emptyTaskList(doingList) == 0){
                printTaskList(doingList);
                printf("Identificador da tarefa\n");
                scanf("%d", &taskId);
                assignDoingDone(doingList, doneList, taskId);
            }else{
                printf("Lista vazia\n");
                getchar();
            }
            break;
        case 10:
            printTaskList(todoList);
            getchar();
            break;
        case 11:
            printTaskList(doingList);
            getchar();
            break;
        case 12:
            printTaskList(doneList);
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
    doingList = createTaskList();
    doneList = createTaskList();

    while (option != 0){
        printf("\e[1;1H\e[2J");

        printf("O nosso projeto em C para Laboratorio de Programacao\n");

        printf("Behold the glorious menu \n\nPlease, select one of following options:\n\n");

        printf("1) Create new task\n2) Delete task\n3) List tasks\n4) Start Task\n5) End Task\n10) List Todo\n11) List Doing\n12) List Done\n\n0) Exit\n\n");
        
        scanf("%d", &option);
        getchar();

        menu(option);
    }


    printf(" I CREATE FILE NOW YES\n");

    FileExists("ola");

    CreateFile("ola");

    FileExists("ola");


    return 0;
}