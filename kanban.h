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
    int state; // 1- ToDo; 2- Doing; 3- Done
    char *description; 
    Date creationDate;
    Date targetDate;
    Date finalDate;
    Person person;
}Task ;

typedef struct node{
    int info;
    Task *Task;
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
void insertItemList (Tasklist list, Task task);
void deletItemList (Tasklist list, int item);

Tasklist searchList (Tasklist list, Task task); //Using task to search
Tasklist searchList (Tasklist list, int task); //Using task Identifier to search

void printlist (Tasklist lista);





#endif