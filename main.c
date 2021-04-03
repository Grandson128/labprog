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
            getchar();//nao está a funcionar, o print de cima nao chega a aparecer
                      //nem espera pelo input. help!!!
            break;

        case 3:
            clearScreen();
            printTaskList(creationDateList);
            printf("Press ENTER to proceed\n");
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

        printf("1) Create new task\n2) Delete task\n3) List tasks\n4) Start Task\n5) End Task\n10) List Todo\n11) List Doing\n12) List Done\n\n0) Exit\n\n");
        
        scanf("%d", &option);
        getchar();

        menu(option);
    }

    saveInFile("data", creationDateList);

    clearScreen();
    return 0;
}
