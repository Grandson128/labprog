#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kanban.h"
#include <string.h>

int TASKS_ID=0; //contagem de tasks criadas
int PEOPLE_ID=0;

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
    Tasklist l = list->next; /* Salta o header */
    while (l){

        printf("Task ID: %d {\n", l->task->id);
        printf("    Description: %s", l->task->description);
        printf("    Priority: %d \n", l->task->priority);
        printf("    Assigned to: %s", l->task->person);
        printf("    Creation Date: %d/%d/%d \n", l->task->creationDate->day,l->task->creationDate->month, l->task->creationDate->year);
        printf("    Goal Date: %d/%d/%d \n", l->task->targetDate->day,l->task->targetDate->month, l->task->targetDate->year);

        if(l->task->finalDate != NULL)
            printf("    Final Date: %d/%d/%d \n", l->task->creationDate->day,l->task->creationDate->month, l->task->creationDate->year);

        l=l->next;
        printf("}\n\n");
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
    clearScreen();

    printf("Describe the task you would like to add\n\n   => ");
    new->description=(char *)malloc(MAX_SIZE*sizeof(char));
    fgets(new->description,MAX_SIZE,stdin);

    printf("\nSet a priority(1-10)for given task\n\n   => ");
    scanf("%d",&new->priority);
    if( new->priority<=0 || new->priority >=11 ){
        printf("\nPlease insert a valid number between 1 and 10\n");
        scanf("%d",&new->priority);
    }

    printf("\nWhen will the task start?\n");
    new->creationDate=setDate();
    if(validateDate(new->creationDate)==1){
        printf("Given date was not valid\n");
        new->creationDate=setDate();
    }

    printf("\nWhen do you plan to finish the task?\n");
    new->targetDate=setDate();
    if(validateDate(new->targetDate)==1){
        printf("Given date was not valid\n");
        new->targetDate=setDate();
    }

    //simplesmente escreve-se o nome da pessoa, não temos em conta o id da pessoa
    printf("\nWho will be in charge?\n\n   => ");
    new->person=(char *)malloc(MAX_SIZE*sizeof(char));
    fgets(new->person,MAX_SIZE,stdin);

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

    new->task = task;
    new->info = 0;
    list-> info++;
    list->lastID = task->id;

    while(strcmp(task->person, current->task->person) > 0 && current->next != NULL){
        previous = current;
        current = current->next;
    }

    if(strcmp(task->person, current->task->person) < 0){
        previous->next = new;
        new->next = current;
    }else{
        new->next = current->next;
        current->next = new;
    }


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

    new->task = task;
    new->info = 0;
    list-> info++;
    list->lastID = task->id;

    if(task!=NULL && current == NULL){
        new->next = current;
        previous->next = new;
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
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }

    printf("File created and saved successfully. \n");

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

void saveInFile(const char *filename, Tasklist list){
    FILE *file;
    file = fopen(filename, "w");

    //creationDateList
    Tasklist l = list->next; /* Salta o header */
    while (l){
        fprintf(file,"Task ID: %d {\n", l->task->id);
        fprintf(file,"    Description: %s", l->task->description);
        fprintf(file,"    Priority: %d \n", l->task->priority);
        fprintf(file,"    Assigned to: %s", l->task->person);
        fprintf(file,"    Creation Date: %d/%d/%d \n", l->task->creationDate->day,l->task->creationDate->month, l->task->creationDate->year);
        fprintf(file,"    Goal Date: %d/%d/%d \n", l->task->targetDate->day,l->task->targetDate->month, l->task->targetDate->year);

        if(l->task->finalDate != NULL)
            fprintf(file,"    Final Date: %d/%d/%d \n", l->task->creationDate->day,l->task->creationDate->month, l->task->creationDate->year);

        l=l->next;
        fprintf(file,"}\n\n");
    }

    fclose(file);
}
