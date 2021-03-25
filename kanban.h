#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>


/**
 * 
 *  Structures Declaration  
 * 
 ***/

typedef struct node* Tasklist;

typedef struct task {
    int id;
    int priority; 
    char *description; 
    Date *creationDate;
    Date *targetDate;
    Date *finalDate;
    Person person;
}Task ;

typedef struct node{
    int info;
    int lastID;
    Task *task;
    Tasklist next;
}Node;

typedef struct {
    int day;
    int month;
    int year;
}Date;

typedef struct{
    int id;
    char *name;
}Person;



/**
 *
 *  
 * Functions Declaration 
 * 
 * 
 **/

Tasklist createTaskList();
Tasklist removeTaskList (Tasklist list);
int emptyList (Tasklist list);
int fullList (Tasklist list);


void insertTask (Tasklist list, Task *task);
void insertTodoTask (Tasklist list, Task *task);
void insertDoingTask (Tasklist list, Task *task);
void insertDoneTask (Tasklist list, Task *task);




void deleteTask (Tasklist list, int item);
Tasklist searchTask (Tasklist list, int task); //Using task Identifier to search
void printlist (Tasklist list);





#endif