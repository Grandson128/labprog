#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kanban.h"
#include <string.h>

int TASKS_ID=0; //contagem de tasks criadas
int PEOPLE_ID=0;
int MAX_DOING_TASKS=5; //max number of doing tasks
int MAX_SIZE=254;

void clearScreen(){
    printf("\e[1;1H\e[2J");
}

/***********************************************************/
/************************ TASKLISTS ************************/
/***********************************************************/


/**
 *
 *  Creates an empty tasklist
 *
 **/
Tasklist createTaskList(){
    Tasklist aux;

    aux = (Tasklist)malloc(sizeof(Node));

    if (aux != NULL) {
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

    while (emptyTaskList(list) == 0){
        temp_ptr = list;
        list = list->next;
        free(temp_ptr);
    }

    free(list);
    return NULL;
}


int emptyTaskList(Tasklist list){
    return (list->next == NULL ? 1 : 0);
}

//não há limite máximo definido para o tamanho da lista
int fullTaskList(Tasklist list){
   return 0;
}

int countTaskList(Tasklist list){

    int count = 0;
    while(list)
    {
        count++;
        list=list->next;
    }

    return count;
}

/**
 *
 *  Prints task list
 *
 **/
void printTaskList (Tasklist list){
    Tasklist l = createTaskList();
    if(list->next != NULL)
        l = list->next; /* Salta o header */
    else{
        printf("Empty list\n\n");
        return;
    }

    while (l != NULL){

        printf("Task ID: %d {\n", l->task->id);
        printf("    Description: %s\n", l->task->description);
        printf("    Priority: %d \n", l->task->priority);
        if(l->task->person != NULL){
            printf("    Assigned to: %s", l->task->person);
        }
        printf("    Creation Date: %d/%d/%d \n", l->task->creationDate->day,l->task->creationDate->month, l->task->creationDate->year);
        printf("    Goal Date: %d/%d/%d \n", l->task->targetDate->day,l->task->targetDate->month, l->task->targetDate->year);

        if(l->task->finalDate != NULL)
            printf("    Final Date: %d/%d/%d \n", l->task->finalDate->day,l->task->finalDate->month, l->task->finalDate->year);

        l=l->next;
        printf("}\n\n");
    }

}

/**
 * 
 * Print all lists
 * 
*/
void printBoard(Tasklist todoList, Tasklist doingList, Tasklist doneList){

    /**
     * 
     * Lado a Lado
     * 
    */

    // Tasklist todo = createTaskList();
    // Tasklist doing = createTaskList();
    // Tasklist done = createTaskList();
    // if(todoList->next != NULL ){todo=todoList->next;}else{todo = NULL;}
    // if(doingList->next != NULL ){doing=doingList->next;}else{doing = NULL;}
    // if(doneList->next != NULL ){done=doneList->next;}else{done = NULL;}
    
    
    // printf("TODO%6s   |%6sDOING%6s|%6sDONE\n","","","","");
    // while (todo != NULL || doing != NULL || done != NULL){
        
    //     /*ID*/
    //     if(todo==NULL) printf("%6s",""); else printf("ID:%6d", todo->task->id);
    //     if(doing==NULL) printf("    |%6s%6s     |","",""); else printf("| ID:%6d |", doing->task->id);
    //     if(done==NULL) printf("%6s\n",""); else printf("ID:%6d\n", done->task->id);

        

    //     /*Description*/
    //     // if(todo==NULL) printf(""); else printf("Descp:%6s", todo->task->description);
    //     // if(doing==NULL) printf(""); else printf("|Descp:%6s|", doing->task->description);
    //     // if(done==NULL) printf("\n"); else printf("Descp:%6s\n", done->task->description);

    //     /*Priority*/
    //     if(todo==NULL) printf("%s",""); else printf("Priority:%d", todo->task->priority);
    //     if(doing==NULL) printf("   |%6s%6s     |","",""); else printf("|Priority:%d|", doing->task->priority);
    //     if(done==NULL) printf("\n"); else printf("Priority:%d\n", done->task->priority);

    //     /*Person*/
    //     if(todo==NULL) printf("%s",""); else if(todo->task->person != NULL) printf("Person:%6s", todo->task->person); else printf("%s",""); 
    //     if(doing==NULL) printf("%6s%6s |%6s%6s     |","","","",""); else if(doing->task->person != NULL) printf("|Person:%6s|", doing->task->person); else printf("%s",""); 
    //     if(done==NULL) printf("\n"); else if(done->task->person != NULL) printf("Person:%6s\n", done->task->person); else printf("\n"); 

    //     /*Creation Date*/
    //     if(todo==NULL) printf("%s",""); else printf("C: %d/%d/%d", todo->task->creationDate->day, todo->task->creationDate->month, todo->task->creationDate->year);
    //     if(doing==NULL) printf("|%6s%6s     |","",""); else printf("|C: %d/%d/%d|", doing->task->creationDate->day, doing->task->creationDate->month, doing->task->creationDate->year);
    //     if(done==NULL) printf("\n"); else printf("C: %d/%d/%d\n", done->task->creationDate->day, done->task->creationDate->month, done->task->creationDate->year);

    //     /*Goal Date*/
    //     if(todo==NULL) printf("%s",""); else printf("G: %d/%d/%d", todo->task->targetDate->day, todo->task->targetDate->month, todo->task->targetDate->year);
    //     if(doing==NULL) printf("|%6s%6s     |","",""); else printf("|G: %d/%d/%d |", doing->task->targetDate->day, doing->task->targetDate->month, doing->task->targetDate->year);
    //     if(done==NULL) printf("\n"); else printf("G: %d/%d/%d \n", done->task->targetDate->day, done->task->targetDate->month, done->task->targetDate->year);

    //     /*Final Date*/
    //     if(todo==NULL) printf("%s",""); else if(todo->task->finalDate != NULL) printf("F: %d/%d/%d", todo->task->finalDate->day, todo->task->finalDate->month, todo->task->finalDate->year); else printf("%s",""); 
    //     if(doing==NULL) printf("%6s%6s |%6s%6s     |","","","",""); else if(doing->task->finalDate != NULL) printf("|F: %d/%d/%d |", doing->task->finalDate->day, doing->task->finalDate->month, doing->task->finalDate->year); else printf("%6s%6s |%6s%6s     |","","","",""); 
    //     if(done==NULL) printf("\n"); else if(done->task->finalDate != NULL) printf("F: %d/%d/%d \n", done->task->finalDate->day, done->task->finalDate->month, done->task->finalDate->year); else printf("%s\n",""); 

    //     printf("<========>\n");

    //     if(todo!=NULL && todo->next != NULL && todo->next->task != NULL ){todo=todo->next;}else{todo = NULL;}
    //     if(doing!=NULL && doing->next != NULL && doing->next->task != NULL ){doing=doing->next;}else{doing = NULL;}
    //     if(done!=NULL && done->next != NULL && done->next->task != NULL ){done=done->next;}else{done = NULL;}

    // }
    // printf("\n");


    /**
     * Sequencial
     * 
     * 
    */
    printf("\t\t<====== To Do List ======>\n");
    printTaskList(todoList);
    printf("\t\t<====== ========= ======>\n\n\n");

    printf("\t\t<====== Doing List ======>\n");
    printTaskList(doingList);
    printf("\t\t<====== ========= ======>\n\n\n");

    printf("\t\t<====== Done List ======>\n");
    printTaskList(doneList);
    printf("\t\t<====== ========= ======>\n\n\n");
}

/*******************************************************/
/************************ TASKS ************************/
/*******************************************************/

Task *createTask(void){


    int ID=TASKS_ID++;

    Task *new = (Task *)malloc(sizeof(Task));
    new->id=ID;
    clearScreen();

    printf("Describe the task you would like to add\n\n   => ");
    new->description=(char *)malloc(MAX_SIZE*sizeof(char));
    fgets(new->description,MAX_SIZE,stdin);

    new->description[strcspn(new->description, "\n")] = 0; //deleta o \n do stdin



    printf("\nSet a priority(1-10)for given task\n\n   => ");
    scanf("%d",&new->priority);

    if(new->priority<1 || new->priority > 10){
        while(new->priority<1 || new->priority >10 ){
            printf("\nPlease insert a valid number between 1 and 10\n\n   => ");
            scanf("%d",&new->priority);
<<<<<<< HEAD
            
        }
        else{
            break;
=======
            char c;
            while((c = getchar()) != '\n' && c != EOF);
>>>>>>> b2347bbc818a447dbf8d0fda119e78a28cfc1704
        }
    }

    printf("\nWhen will the task start?\n");
    new->creationDate=setDate();
    while(1){
        if(validateDate(new->creationDate)==1){
            printf("Given date was not valid\n");
            new->creationDate=setDate();
        }
        else{
            break;
        }
    }

    printf("\nWhen do you plan to finish the task?\n");
    new->targetDate=setDate();
    while(1){
        if(validateDate(new->targetDate)==1){
            printf("Given date was not valid\n");
            new->targetDate=setDate();
        }
        else{
            break;
        }
    }

   new->finalDate=NULL;

    return new;

}


/**
 *
 *  Returns a list where the first task element has the same identification as the one given
 *  @list - task list with our task
 *  @task - task identifier
 *
 **/
Task *searchTask(Tasklist list, int task){
    int targetValue = task;
    Tasklist previous = list;
    Tasklist current = list->next;

    while ((current) != NULL && (current)->task->id != targetValue){
        previous = current;
        current = (current)->next;
    }

    //free(previous);

    if ((current) != NULL && (current)->task->id != targetValue){
        current = NULL;
        /* Se elemento não encontrado*/
        return NULL;
    }

    return current->task;
}

/**
 * Function to check if a task is in a given list
 *
 * @list - List with task's
 * @targetTaskId - Task identifier
 *
 * Return:
 * 1 - Task found in list
 * 0 - Task not found
*/
int taskIn(Tasklist list, int targetTaskId){

    if(list->next == NULL)
        return 0;

    Tasklist current  = list->next;
    Tasklist previous = list;

    if (current != NULL && current->task->id == targetTaskId){
        return 1;
    }

    while(current->next != NULL && current->task->id != targetTaskId){
        previous = current;
        current = current->next;
    }

    if(current != NULL && current->task != NULL && current->task->id == targetTaskId){
        return 1;
    }else{
        return 0;
    }


}

/**
 * Add's task to list
 * Orders by Creation Date
 * @list - list to add task
 * @task - pointer to task to add
 **/
void insertTask(Tasklist list, Task *task){
    Tasklist previous = list;
    Tasklist current = list->next;
    Tasklist new = (Tasklist)malloc(sizeof(Node));

    new->task = task;
    new->info = 0;
    list-> info++;
    list->lastID = task->id;

    if(task!=NULL && current == NULL){
        new->next = current;
        previous->next = new;
    }

    else if(task != NULL && current != NULL){

        while (compareDate(task->creationDate,current->task->creationDate) == 1 && current->next != NULL ){
            previous = current;
            current = current->next;
        }

        if(compareDate(task->creationDate, current->task->creationDate) != 1){
            previous->next = new;
            new->next = current;
        }

        if(compareDate(task->creationDate, current->task->creationDate)){
            new->next = current->next;
            current->next = new;
        }
    }

    //update File
    //saveInFile("creation", list);
}

/**
 * Add's task to list
 * Orders by Priority and by Creation Date
 * @list - list to add task
 * @task - pointer to task to add
 **/
void insertTodoTask (Tasklist list, Task *task){
    Tasklist previous = list;
    Tasklist current = list->next;
    Tasklist new = (Tasklist)malloc(sizeof(Node));

    new->task = task;
    new->info = 0;
    list-> info++;
    list->lastID = task->id;

    if(task!=NULL && current == NULL){
        new->next = current;
        previous->next = new;
    }else if(task!=NULL && current != NULL){

        while (task->priority < current->task->priority){
            previous = current;
            current = current->next;
        }

        if(task->priority > current->task->priority){
            previous->next = new;
            new->next = current;
        }else if(task->priority < current->task->priority){
            new->next = current->next;
            current->next = new;

        }else if(task->priority == current->task->priority){

            while (compareDate(task->creationDate,current->task->creationDate) == 1 && (task->priority == current->task->priority) && current->next != NULL ){
                previous = current;
                current = current->next;
            }

            if(compareDate(task->creationDate, current->task->creationDate) != 1){
                previous->next = new;
                new->next = current;
            }

            if(compareDate(task->creationDate, current->task->creationDate)){
                new->next = current->next;
                current->next = new;
            }

        }

    }

    //update File
    //saveInFile("todo", list);

}

/**
 * Add's task to list
 * Orders by persons name
 * @list - list to add task
 * @task - pointer to task to add
 **/
void insertDoingTask (Tasklist list, Task *task){
    Tasklist previous = list;
    Tasklist current = list->next;
    Tasklist new = (Tasklist)malloc(sizeof(Node));

    if(task == NULL)
        return;

    new->task = task;
    new->info = 0;
    list->info++;
    list->lastID = task->id;

    if (emptyTaskList(list) == 1){
        list->next = new;
        return;
    }

    while(strcmp(task->person, current->task->person) > 0 && current->next != NULL){
        previous = current;
        current = current->next;
    }

    if(strcmp(task->person, current->task->person) < 0){
        previous->next = new;
        new->next = current;
    }
    else {
        new->next = current->next;
        current->next = new;
    }

    //update Files
    saveInFile("doing", list);
}

/**
 * Add's task to list
 * Orders by final date
 * @list - list to add task
 * @task - pointer to task to add
 **/
void insertDoneTask (Tasklist list, Task *task){
    Tasklist previous = list;
    Tasklist current = list->next;
    Tasklist new = (Tasklist)malloc(sizeof(Node));

    printf("\nTask final date?\n");
    task->finalDate=setDate();
    if(validateDate(task->finalDate)==1){
        printf("\nGiven date was not valid\n");
        task->finalDate=setDate();
    }

    new->task = task;
    new->info = 0;
    list-> info++;
    list->lastID = task->id;

    if (emptyTaskList(list) == 1){
        list->next = new;
        return;
    }

    else if(task != NULL && current != NULL){

        while (compareDate(task->finalDate,current->task->finalDate) == 1 && current->next != NULL ){
            previous = current;
            current = current->next;
        }

        if(compareDate(task->finalDate, current->task->finalDate) != 1){
            previous->next = new;
            new->next = current;
        }

        if(compareDate(task->finalDate, current->task->finalDate)){
            new->next = current->next;
            current->next = new;
        }
    }

    //update Files
    saveInFile("done", list);
}

/**
 * Removes task from task list
 *
 * @list - list with task pointer
 * @targetTaskId - task identifier
 **/
void deleteTask(Tasklist list, int targetTaskId){
    Tasklist current  = list->next;
    Tasklist previous = list;

    if (current != NULL && current->task->id == targetTaskId){
        previous->next = current->next;
        free(current);
        return;
    }

    while(current->next != NULL && current->task->id != targetTaskId){
        previous = current;
        current = current->next;
    }

    if(current == NULL)
        return;

    previous->next = current->next;
    free(current);
    list->info--;
    //TODO: Handle task removal in file

}

/**
 * Thanos snap on tasks
 *
 * @list - list with task pointer
 * @todoList - list with task pointer
 * @doingList - list with task pointer
 * @doneList - list with task pointer
 * @targetTaskId - task identifier
 **/
void purgeTask(Tasklist list, Tasklist todoList, Tasklist doingList, Tasklist doneList, int targetTaskId){
    deleteTask(list, targetTaskId);
    deleteTask(todoList, targetTaskId);
    deleteTask(doingList, targetTaskId);
    deleteTask(doneList, targetTaskId);
}

/**
 * Function to "pause" the program until user input
 *  2 getchat used because only 1 was beeing ignored
*/
void mypause ( void ) {
  printf ( "Press ENTER to continue...\n");
  fflush (NULL);
  getchar();
}

/**
 * Function to assign a task from todo list to the doing list
 *
 * @todolist - List with Todo tasks
 * @doinglist - List with Doing tasks
 * @taskId - Task identifier
 *
*/
void assignTodoDoing(Tasklist todoList, Tasklist doingList, int taskId){
    if (taskIn(todoList, taskId) == 1){

        if(doingList->info >= MAX_DOING_TASKS){
            printf("Max number of tasks reached\n");
            mypause();
            return;
        }

        Task *new = searchTask(todoList,taskId);

        char c;
        while((c = getchar()) != '\n' && c != EOF); //limpa o stdin para o fgets funcionar. o fflush nao estava a funcionar

        //simplesmente escreve-se o nome da pessoa, não temos em conta o id da pessoa
        printf("\nWho will be in charge?\n\n   => ");
        new->person=(char *)malloc(MAX_SIZE*sizeof(char));
        fgets(new->person,50,stdin);

        insertDoingTask(doingList, new);
        clearScreen();
        //printTaskList(doingList);
        deleteTask(todoList, taskId);

        //remove from file
        if(emptyTaskList(todoList) != 1) saveInFile("todo", todoList); else clearFile("todo");

        printf("Task initiated\n\n");

    }
    else {
        printf("Given ID was not valid,returning to option menu\n");
        sleep(2);
    }
    mypause();
}

/**
 Function to assign a task from doing list to the todo list
 *
 * @todolist - List with Todo tasks
 * @doinglist - List with Doing tasks
 * @taskId - Task identifier
 * 
*/
void assignDoingTodo(Tasklist todoList, Tasklist doingList, int taskId){
    if (taskIn(doingList, taskId) == 1){
        Task *new = searchTask(doingList,taskId);

        char c;
        while((c = getchar()) != '\n' && c != EOF);

        new->person = NULL;

        insertTodoTask(todoList,new);
        clearScreen();
        deleteTask(doingList,taskId);

        //remove from file
        if(emptyTaskList(doingList) != 1) saveInFile("doing", doingList); else clearFile("doing");

        printf("Task moved to To Do\n\n");

    }
    else {
        printf("Given ID was not valid,returning to option menu\n");
        sleep(2);
    }
    mypause();
}

/**
 * Function to assign a task from done list to the todo list
 *
 * @donelist - List with Done tasks
 * @todolist - List with Todo tasks
 * @taskId - Task identifier
*/
void assignDoneTodo(Tasklist doneList, Tasklist todoList, int taskId){

    if (taskIn(doneList, taskId) == 1){
        Task *new = searchTask(doneList,taskId);

        char c;
        while((c = getchar()) != '\n' && c != EOF);

        new->person = NULL;
        new->finalDate = NULL;

        insertTodoTask(todoList,new);
        clearScreen();
        deleteTask(doneList,taskId);

        //remove from file
        if(emptyTaskList(doneList) != 1) saveInFile("doing", doneList); else clearFile("done");

        printf("Task moved to To Do\n\n");

    }
    else {
        printf("Given ID was not valid,returning to option menu\n");
        sleep(2);
    }
    mypause();
}

/**
 * Function to assign a task from doing list to the done list
 *
 * @todolist - List with Doing tasks
 * @doinglist - List with Done tasks
 * @taskId - Task identifier
 *
*/
void assignDoingDone(Tasklist doingList, Tasklist doneList, int taskId){
    if (taskIn(doingList, taskId) == 1){
        insertDoneTask(doneList, searchTask(doingList, taskId));
        clearScreen();
        //printTaskList(doneList);
        deleteTask(doingList, taskId);

        //remove from file
        if(emptyTaskList(doingList) != 1) saveInFile("doing", doingList); else clearFile("doing");

        printf("Task terminated\n");

    }
    else {
        printf("Given ID was not valid,returning to option menu\n");
        sleep(2);
    }

    mypause();
}


/*******************************************************/
/************************ DATES ************************/
/*******************************************************/


/**
 *
 *  Creates and sets new date
 *
 **/
Date *setDate(){
    Date *new = (Date *)malloc(255*sizeof(Date));

    printf("Insert the date in the following format: DD/MM/AAAA\n\n   => ");
    scanf("%d/%d/%d",&new->day,&new->month,&new->year);
    getchar(); //?

    return new;
}


void changeDate(Date *date) { //void ou date * ? como apenas dados do apontador, assumi que fosse void
    printf("Insert new date in the following format:\n DD/MM/AAAA \n");
    scanf("%d/%d/%d",&date->day,&date->month,&date->year);
    getchar(); //?

    //return date;
}

/**
 *
 *  Validates the given date. Returns 1 if NOT valid.
 *
 **/
int validateDate(Date *date){

    int dd= (date->day);
    int mm= (date->month);
    int yy= (date->year);

    if(yy>=0)
    {
        if(mm>=1 && mm<=12)
        {
            if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12)) {
                printf("\nDate is valid.\n");
                return 0;
            }
            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11)) {
                printf("\nDate is valid.\n");
                return 0;
            }
            else if((dd>=1 && dd<=28) && (mm==2)) {
                printf("\nDate is valid.\n");
                return 0;
            }
            else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0))) {
                printf("\nDate is valid.\n");
                return 0;
            }
            else {
                printf("\nDay is not valid.\n");
                return 1;
            }
        }
        else
        {
            printf("Month is not valid.\n");
            return 1;
        }
    }
    else
    {
        printf("Year is not valid.\n");
        return 1; // se calhar aqui este return é redondante
    }

    return 1;
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


/*******************************************************/
/*********************** PERSON ************************/
/*******************************************************/


void changePerson(Tasklist list, int targetTaskId){
    printf("\nInsert new admin name for this task\n\n   => ");
    Task *new = searchTask(list,targetTaskId);
    char c;
    while((c = getchar()) != '\n' && c != EOF);
    new->person=(char *)malloc(50*sizeof(char));
    fgets(new->person,MAX_SIZE,stdin);
    return;
    /*
    while(1){
        if(previous->task->id == targetTaskId){
            char c;
            while((c = getchar()) != '\n' && c != EOF);
            previous->task->person=(char *)malloc(50*sizeof(char));
            fgets(previous->task->person,MAX_SIZE,stdin);
            return;
        }
        else if(current->task->id == targetTaskId){
            char c;
            while((c = getchar()) != '\n' && c != EOF);
            current->task->person=(char *)malloc(50*sizeof(char));
            fgets(current->task->person,MAX_SIZE,stdin);
            return;
        }
        previous = current;
        current = current->next;
    }
    return;*/
}

void tasksByPerson(Tasklist list, const char *name){

    Tasklist l = createTaskList();
     if(list->next != NULL)
        l = list->next; /* Salta o header */
    else{
        printf("Currently empty list\n");
        return;
    }

    while( l != NULL){

        if(strcmp(name,l->task->person)) {
            printf("Task ID: %d {\n", l->task->id);
            printf("    Priority: %d \n", l->task->priority);
            printf("    Assigned to: %s", l->task->person);
            printf("    Creation Date: %d/%d/%d \n", l->task->creationDate->day,l->task->creationDate->month, l->task->creationDate->year);
            printf("    Goal Date: %d/%d/%d \n", l->task->targetDate->day,l->task->targetDate->month, l->task->targetDate->year);
            if(l->task->finalDate != NULL)
                printf("    Final Date: %d/%d/%d \n", l->task->finalDate->day,l->task->finalDate->month, l->task->finalDate->year);
            l=l->next;
            printf("}\n\n");
        }
        else {
        printf("%s has no tasks in this fase\n", name);
        }

    }

}

/*******************************************************/
/************************ FILES ************************/
/*******************************************************/



/*
 * Check if a file exist using fopen() function
 * return 1 if the file exist otherwise return 0
 */
int FileExists(const char *filename){
    /* try to open file to read */
    FILE *file;
    if (file = fopen(filename, "r")){
        fclose(file);
        return 1;
    }
    return 0;
}

/**
 * Function that creates a file if the file doesn't exist, if it does exist, does nothing
*/
void CreateFile(const char *filename) {
    FILE *file;
    /*
     * Open file in w (write) mode.
     * "data/file1.txt" is complete path to create file
     */
    file = fopen(filename, "w");
    /* fopen() return NULL if last operation was unsuccessful */
    if(file == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create %s file.\n", filename);
        exit(EXIT_FAILURE);
    }
    //printf("File %s created and saved successfully. \n", filename);
    fclose(file);
}


//introduzir tasks de um certo file na tasklist indicada (inicio do programa)
/*
Task readFiles(const char *filename, int contagem, int flag){
    FILE *file;
    file = fopen(filename, "r");
    int MAX_SIZE=50;
    int ID=TASKS_ID++;
    char buffer[MAX_SIZE];
    Task *new = (Task *)malloc(sizeof(Task));

    if(file == NULL){
        exit(EXIT_FAILURE);
    }

    for(int i=0; i<contagem*8; i++){ //ignorar tasks já introduzidas
        fgets(buffer, MAX_SIZE, file);
    }

    while(fgets(buffer, MAX_SIZE, file)){   //ler linha-a-linha o ficheiro
        if(buffer[0] == 'T'){   //Caso encontre o inicio de uma nova task
            int line=1;
            new->id=ID;
            new->finalDate=NULL;
            while(fgets(buffer,MAX_SIZE,file)){
                if(line==1){    //Descriçao
                    int i=0;
                    char descricao[MAX_SIZE];
                    while(buffer[i+18]!='\n'){  //inicio da descriçao=> i=18. fim da descriçao=> '\n'
                        descricao[i]=buffer[i+18];
                        i++;
                    }
                    new->description= (char *)malloc(MAX_SIZE*sizeof(char)); //nao sei se é necessario
                    new->description= descricao;
                }
                else if(line==2){    //Prioridade
                    if(buffer[15]=='0'){
                        new->priority = 10; //unico numero com 2 dígitos possivel
                    }
                    else{
                        new->priority = buffer[14];
                    }
                }
                else if(line==3){    //Pessoa
                    int i=0;
                    char nome[MAX_SIZE];
                    while(buffer[i+17] != '\n'){
                        nome[i]=buffer[i+17];
                        i++;
                    }
                    new->person= (char *)malloc(MAX_SIZE*sizeof(char));  //nao sei se é necessario
                    new->person= nome;
                }
                else if(line==4){    //Data de Criaçao
                    new->creationDate->day = buffer[19]*10 + buffer[20];
                    new->creationDate->month = buffer[22]*10 + buffer[23];
                    new->creationDate->year = buffer[25]*1000 + buffer[26]*100 + buffer[27]*10 + buffer[28];
                }
                else if(line==5){
                    new->targetDate->day = buffer[15]*10 + buffer[16];
                    new->targetDate->month = buffer[18]*10 + buffer[19];
                    new->targetDate->year = buffer[21]*1000 + buffer[22]*100 + buffer[23]*10 + buffer[24];
                }
                line++;

            }
        }
    }
    fclose(file);
    return new;
}
*/

const char* getDataField(char* line, int num)
{
    const char* token;
    for (token = strtok(line, ";");
            token && *token;
            token = strtok(NULL, ";\n"))
    {
        if (!--num)
            return token;
    }
    return NULL;
}

void fileToTasks(const char *filename,Tasklist list){
    FILE* file = fopen("data", "r");

/*
    Tasklist l = createTaskList();

    char header[50];
    char* tmp =strdup(header);
    l->info=getDataField(tmp,1);
    l->lastID=getDataField(tmp,2);
    free(tmp);*/


    char line[1024];
  //  Task *new = (Task *)malloc(sizeof(Task));
    
    while (fgets(line, 1024, file)){
        Task *new = (Task *)malloc(sizeof(Task));
        char* tmp = strdup(line);

        new->id=getDataField(tmp,1);
        new->description=getDataField(tmp,2);
        new->priority=getDataField(tmp,3);
        new->person=getDataField(tmp,4);

        new->creationDate->day=getDataField(tmp,5);
        new->creationDate->month=getDataField(tmp,6);
        new->creationDate->year=getDataField(tmp,7);

        new->targetDate->day=getDataField(tmp,8);
        new->targetDate->month=getDataField(tmp,9);
        new->targetDate->year=getDataField(tmp,10);

        new->targetDate->day=getDataField(tmp,11);
        new->targetDate->month=getDataField(tmp,12);
        new->targetDate->year=getDataField(tmp,13);

        insertTask(list, new);
        //  insertTodoTask(list, new);
        //printTaskList(list);

        free(tmp);
    }
   //  printTaskList(list);
        fclose(file);
}

/**
 * 
 * Saves list in file
 * SAVE FORMAT:
 * ****list info:
 * [nº tasks];[last task identifier];
 * ****tasks:
 * [id];[description];[priority];[person];[creation day];[creation month];[creation year];[target day];[target month];[target year];[final day];[final month];[final year]
 * 
*/
void saveInFile(const char *filename, Tasklist list){

    if(list==NULL)
        return;

    FILE *file;
    file = fopen(filename, "w");

    /*
    fprintf(file,"%d", list->info); 
    fprintf(file,";%d", list->lastID); 
    fprintf(file,";\n");
    */
    //creationDateList

    if(list->next == NULL){
        fclose(file);
        return;
    }

    Tasklist l = list->next; /* Salta o header */

    while (l != NULL){
        fprintf(file,"%d", l->task->id);
        fprintf(file,";%s", l->task->description);
        fprintf(file,";%d", l->task->priority);

         if(l->task->person != NULL) {
            fprintf(file,";%s", l->task->person);
        }
        else 
            fprintf(file,";");

        fprintf(file,";%d", l->task->creationDate->day);
        fprintf(file,";%d", l->task->creationDate->month);
        fprintf(file,";%d", l->task->creationDate->year);

        fprintf(file,";%d", l->task->targetDate->day);
        fprintf(file,";%d", l->task->targetDate->month);
        fprintf(file,";%d", l->task->targetDate->year);


         if(l->task->finalDate != NULL) {
              fprintf(file,";%d", l->task->finalDate->day);
            fprintf(file,";%d", l->task->finalDate->month);
            fprintf(file,";%d", l->task->finalDate->year);
        }
        else
            fprintf(file,";");

        l=l->next;
        fprintf(file,";\n");
    }

    fclose(file);
}

/**
 * Function that deletes all the content of a file
*/
void clearFile(const char *filename){
    FILE *file;
    file = fopen(filename, "w");
    fclose(file);
}