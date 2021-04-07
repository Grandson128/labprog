
#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/**
 *
 *  Structures Declaration
 *
 ***/
typedef struct date{
    int day;
    int month;
    int year;
}Date;

typedef struct task {
    int id;
    int priority;
    char *description;
    Date *creationDate;
    Date *targetDate;
    Date *finalDate;
    char *person;
}Task;

typedef struct node* Tasklist;

typedef struct node{
    int info;
    int lastID;
    Task *task;
    Tasklist next;
}Node;

/**
 *
 *
 * Functions Declaration
 *
 *
 **/
Tasklist createTaskList();
Tasklist removeTaskList (Tasklist list);
int emptyTaskList (Tasklist list);
void printTaskList (Tasklist list);
void printBoard(Tasklist todoList, Tasklist doingList, Tasklist doneList);

Task *createTask();
Task *searchTask (Tasklist list, int task); 
int taskIn(Tasklist list, int targetTaskId);
void insertTask (Tasklist list, Task *task);
void insertTodoTask (Tasklist list, Task *task);
void insertDoingTask (Tasklist list, Task *task);
void insertDoneTask (Tasklist list, Task *task);
void assignTodoDoing(Tasklist todoList, Tasklist doingList, int taskId);
void assignDoingDone(Tasklist doingList, Tasklist doneList, int taskId);
void assignDoneTodo(Tasklist doneList, Tasklist todoList, int taskId);
void deleteTask (Tasklist list, int item);
void purgeTask(Tasklist list, Tasklist todoList, Tasklist doingList, Tasklist doneList, int targetTaskId);
void assignDoingTodo(Tasklist todoList, Tasklist doingList, int taskId);

Date *setDate();
int validateDate(Date *date);
int compareDate(Date *date1, Date *date2);
Date *createDate(int day, int month, int year);

void changePerson(Tasklist list, int targetTaskId);
void tasksByPerson(Tasklist list, const char *name);

void saveInFile(const char *filename, Tasklist list);
void clearFile(const char *filename);
Tasklist fileToTasks(const char *filename);
void CreateFile(const char *filename);
int FileExists(const char *filename);

void mypause (void);
void clearScreen(void);

#endif
