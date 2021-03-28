#include <stdio.h>
#include <stdlib.h>
#include "kanban.h"

int TASKS_ID=0; //contagem de tasks criadas
int PEOPLE_ID=0;

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

void printTaskList (Tasklist list){
    Tasklist l = list->next; /* Salta o header */
    while (l){
    printf("%d", l->info);
    l=l->next;
    }
}







/*******************************************************/
/************************ TASKS ************************/
/*******************************************************/

Task *createTask(void){


    int MAX_SIZE=50;
    int ID=TASKS_ID++;

    Task *new = (Task *)malloc(sizeof(Task));
    new->id=ID;

    printf("\n Describe the task you would like to add\n");
    new->description=(char *)malloc(MAX_SIZE*sizeof(char));
    fgets(new->description,MAX_SIZE,stdin);

    printf("\n Set a priority(1-10)for given task\n");
    scanf("%d",&new->priority);
    if( new->priority<=0 || new->priority >=11 ){
        printf("\n Please insert a valid number between 1 and 10");
        scanf("%d",&new->priority);
    }

    printf("\n When will the task start?\n");
    new->creationDate=setDate();
    if(validateDate(new->creationDate)==1){
        printf("\n Given date was not valid \n");
        new->creationDate=setDate();
    }

    printf("\n When do you plan to finish the task?\n");
    new->targetDate=setDate();
    if(validateDate(new->targetDate)==1){
        printf("\n Given date was not valid \n");
        new->targetDate=setDate();
    }

    //simplesmente escreve-se o nome da pessoa, não temos em conta o id da pessoa
    printf("\n Who will be in charge?\n");
    new->person=*setPerson();

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






/**
 *
 *
 * Add's task to list
 * Orders by Creation Date
 * @list - list to add task
 * @task - pointer to task to add
 *
 *
 **/
void insertTask(Tasklist list, Task *task){
    Tasklist previous = list;
    Tasklist current = list->next;
    Tasklist new = (Tasklist)malloc(sizeof(Node));

    new->task = task;
    new->info = 0;
    list-> info++;

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
}

void deleteTask(Tasklist list,int task){

    Tasklist ant1=list;
    Tasklist atual1=list->next;

    searchTask(list, task);
    if (atual1 != NULL) {
        ant1->next = atual1->next;
        free (atual1);
    }
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
    Date *new = (Date *)malloc(sizeof(Date));

    printf("Insert the date in the following format:\n DD/MM/AAAA \n");
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

    if(yy>=2020)
    {
        if(mm>=1 && mm<=12)
        {
            if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12)) {
                printf("Date is valid.\n");
                return 0;
            }
            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11)) {
                printf("Date is valid.\n");
                return 0;
            }
            else if((dd>=1 && dd<=28) && (mm==2)) {
                printf("Date is valid.\n");
                return 0;
            }
            else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0))) {
                printf("Date is valid.\n");
                return 0;
            }
            else {
                printf("Day is not valid.\n");
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
/************************ PEOPLE ***********************/
/*******************************************************/

Person *setPerson(){

    Person *new = (Person *)malloc(sizeof(Person));

    printf("Insert the name of who will be responsible\n");
    scanf("%p",&new->name);

    int ID=PEOPLE_ID++;
    new->id=ID;

    return new;
}
