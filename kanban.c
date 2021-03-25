#include <stdio.h>
#include <stdlib.h>
#include "kanban.h"

/**
 *
 *  Creates an empty tasklist
 *
 **/
Tasklist createTaskList(){
    Tasklist aux;

    aux = (Tasklist)malloc(sizeof(Node));

    if (aux != NULL) {
        aux->lastID = 0;
        aux->info = 0;
        aux->task = NULL;
        aux->next = NULL;
    }
    else {
        printf("No memory available to allocate list");
    }
    return aux;
}

/**
 *
 *  Removes completely from memory a given tasklist
 *
 **/
Tasklist removeTaskList(Tasklist list){
    Tasklist temp_ptr;

    while (emptyList(list) == 0){
        temp_ptr = list;
        list = list->next;
        free(temp_ptr);
    }

    free(list);

    return NULL;
}

int emptyList(Tasklist list){
    return (list->next == NULL ? 1 : 0);
}

int fullList(Tasklist list){
    //ToDo
}

/**
 *
 *  Returns a list where the first task element has the same identification as the one given
 *  @list - task list with our task
 *  @task - task identifier
 *
 **/
Tasklist searchTask(Tasklist list, int task){

    int targetValue = task;
    Tasklist previous = list;
    Tasklist current = list->next;

    while ((current) != NULL && (current)->task->id != targetValue){
        previous = current;
        current = (current)->next;
    }

    free(previous);

    if ((current) != NULL && (current)->task->id != targetValue){
        current = NULL; /* Se elemento não encontrado*/
        return NULL;
    }

    return current;
}

void insertTask(Tasklist list, Task *task){
    Tasklist previous = list;
    Tasklist current = list->next;

    Tasklist new = (Tasklist)malloc(sizeof(Node));

    new->task = task;
    new->info = 0;
    //list-> info++;
    
    
    if(task!=NULL && current == NULL){
        new->next = current;
        previous->next = new;
    }
    else if(task != NULL && current != NULL){
        //ToDo Loop comparing creation date
    }
}

void deleteTask(Tasklist list, int item){
    //ToDo
}

/************************ DATES ************************/

/**
 *
 *  Creates and sets new date
 *
 **/
Date *setDate(){
    Date *new = (Date *)malloc(sizeof(Date));

    printf("Insert date in the following format:\n DD/MM/AAAA \n");
    scanf("%d/%d/%d",&new->day,&new->month,&new->year);
    getchar();

    return new;
}

/**
 *
 *  Validates the given date. Returns 0 if not valid.
 *
 **/
int validateDate(Date *date){

    int dd= (date->day);
    int mm= (date->month);
    int yy= (date->year);

    if(yy>=2020)
    {
        if(mm>=1 && mm<=12)
        {
            if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12)) {
                printf("Date is valid.\n");
                return 1;
            }
            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11)) {
                printf("Date is valid.\n");
                return 1;
            }
            else if((dd>=1 && dd<=28) && (mm==2)) {
                printf("Date is valid.\n");
                return 1;
            }
            else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0))) {
                printf("Date is valid.\n");
                return 1;
            }
            else {
                printf("Day is invalid.\n");
                return 0;
            }
        }
        else
        {
            printf("Month is not valid.\n");
            return 0;
        }
    }
    else
    {
        printf("Year is not valid.\n");
        return 0; // se calhar aqui este return é redondante
    }
 
    return 0;    
}




/**
 *
 * Compares if date1 is after date2
 *
 */
int compareDate(Date *date1, Date *date2){
    if (date1->year > date2->year){
        return 1;
    }

    else if (date1->year == date2->year && date1->month > date2->month){
        return 1;
    }

    else if (date1->year == date2->year && date1->month == date2->month && date1->day > date2->day){
        return 1;
    }

    else{
        return 0;
    }
}