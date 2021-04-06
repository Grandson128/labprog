
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
int fullTaskList (Tasklist list);
int emptyTaskList(Tasklist list);
int countTaskList(Tasklist list);
void printTaskList (Tasklist list);

void insertTask (Tasklist list, Task *task);
void insertTodoTask (Tasklist list, Task *task);
void insertDoingTask (Tasklist list, Task *task);
void insertDoneTask (Tasklist list, Task *task);
void assignTodoDoing(Tasklist todoList, Tasklist doingList, int taskId);
void assignDoingDone(Tasklist doingList, Tasklist doneList, int taskId);
void assignDoneTodo(Tasklist doneList, Tasklist todoList, int taskId);
void assignDoingTodo(Tasklist todoList, Tasklist doingList, int taskId);
void mypause (void);
void purgeTask(Tasklist list, Tasklist todoList, Tasklist doingList, Tasklist doneList, int targetTaskId);
int taskIn(Tasklist list, int targetTaskId);
void tasksByPerson(Tasklist list, const char *name);
void changePerson(Tasklist list, int targetTaskId);
void printBoard(Tasklist todoList, Tasklist doingList, Tasklist doneList);

void deleteTask (Tasklist list, int item);
Task *searchTask (Tasklist list, int task); //Using task Identifier to search
void printlist (Tasklist list);

Date *setDate();
int validateDate(Date *date);
int compareDate(Date *date1, Date *date2); //isto está bem?
Date *createDate(int day, int month, int year);

void saveInFile(const char *filename, Tasklist list);
void clearFile(const char *filename);
Tasklist fileToTasks(const char *filename);
const char* getDataField(char* line, int num);
void CreateFile(const char *filename);
int FileExists(const char *filename);

void mypause (void);
void clearScreen(void);

#endif
