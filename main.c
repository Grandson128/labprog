#include <stdio.h>
#include <stdlib.h>
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
            printTaskList(creationDateList);
            
            getchar();
            break;
        case 2:
            
            printf("Identificador da tarefa a eliminar\n");
            scanf("%d", &taskId);
            deleteTask(creationDateList, taskId);

        case 3:
            printTaskList(creationDateList);
            getchar();

        default:
            break;
        }
}


int main(){
    int option;
    todoList = createTaskList();
    creationDateList = createTaskList();   

    while (option != 0){
        printf("\e[1;1H\e[2J");

        printf("O nosso projeto em C para Laboratorio de Programacao\n");

        printf("Behold the glorious menu \n\nPlease, select one of following options:\n\n");

        printf("1) Create new task\n2) Delete task\n3) List tasks\n0) Exit\n\n");
        
        scanf("%d", &option);
        getchar();

        menu(option);
    }


    return 0;
}