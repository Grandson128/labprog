#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "kanban.c"

Task *newTask;
Tasklist todoList;
Tasklist doingList;
Tasklist doneList;
Tasklist creationDateList;
int taskId;
char name[20];


void banner(){

    printf("|__/  /\\  |\\ | |__)  /\\  |\\ |    |__) /  \\  /\\  |__) |  \\\n");
    printf("|  \\ /~~\\ | \\| |__) /~~\\ | \\|    |__) \\__/ /~~\\ |  \\ |__/\n\n"); 
}

void menu(int option){
    char c;
    switch (option){
        case 1: //CRIAR TAREFA
            newTask = createTask();
            insertTask(creationDateList, newTask);
            insertTodoTask(todoList, newTask);
            clearScreen();
            printTaskList(todoList);
            saveInFile("creation", creationDateList);
            saveInFile("todo", todoList);

            printf("Press ENTER to proceed\n");
            getchar();
            break;

        case 2: //APAGAR TAREFA
            clearScreen();
            printTaskList(creationDateList);
            if(creationDateList->next != NULL){
                printf("Insert the Task ID you wish to delete\n\n   => ");
                scanf("%d", &taskId);

                 while((c = getchar()) != '\n' && c != EOF);

                if (taskIn(creationDateList, taskId) == 1) {
                    deleteTask(creationDateList, taskId);
                    if(emptyTaskList(creationDateList) != 1) 
                        saveInFile("creation", creationDateList);  
                    else 
                        clearFile("creation");

                    if (taskIn(todoList, taskId) == 1 ) {deleteTask(todoList, taskId);  if(emptyTaskList(todoList) != 1) saveInFile("todo", todoList); else clearFile("todo");}
                    if (taskIn(doingList, taskId) == 1 ) {deleteTask(doingList, taskId); if(emptyTaskList(doingList) != 1) saveInFile("doing", doingList); else clearFile("doing");}
                    if (taskIn(doneList, taskId) == 1 ) {deleteTask(doneList, taskId); if(emptyTaskList(doneList) != 1) saveInFile("done", doneList); else clearFile("done");}
                    
                    printf("\nTask Eliminated\nReturning to main menu...\n");
                    sleep(2);

                } else {
                    printf("Invalid task\nReturning to main menu...\n");
                    sleep(1);
                }
                
            } else{
                printf("No tasks to eliminate\nReturning to main menu...\n");
                sleep(1);
            }
            break;

        case 3: //LISTAR TAREFAS
            clearScreen();
            printTaskList(creationDateList);
            printf("Press ENTER to proceed\n");
            getchar();
            break;
        case 4: //ToDo para DOING
            clearScreen();
            if (emptyTaskList(todoList) == 0){
                printTaskList(todoList);
                printf("Insert the task ID you want to transfer to Doing\n\n   => ");
                scanf("%d", &taskId);
                assignTodoDoing(todoList, doingList, taskId);

                //saveInFile("todo", todoList);
                saveInFile("doing", doingList);

            }
            else {
                printf("Empty list\n\nNo tasks on the To Do list\nReturning to main menu...\n");
                sleep(3);
            }
            break;
        case 5: //DOING para ToDO
            clearScreen();
            if(emptyTaskList(doingList) == 0){
                printTaskList(doingList);
                printf("Insert the task ID you want to transfer to ToDo\n\n   => ");
                scanf("%d", &taskId);
                assignDoingTodo(todoList, doingList, taskId);

                //saveInFile("doing", doingList);
                saveInFile("todo", todoList);

            }
            else {
                printf("Empty list\n\nNo Tasks on the To Do list\nReturning to main menu...\n");
                sleep(3);
            }
            break;
        case 6: //DOING para DONE
            clearScreen();
            if (emptyTaskList(doingList) == 0){
                printTaskList(doingList);
                printf("Insert the task ID you want to transfer to Done\n\n   => ");
                scanf("%d", &taskId);
                assignDoingDone(doingList, doneList, taskId);

                //saveInFile("doing", doingList);
                saveInFile("done", doneList);

            }
            else {
                printf("Empty list\n\nNo tasks on the Doing list\nReturning to main menu...\n");
                sleep(3);
            }
            break;
        case 7: //CHANGE ADMIN
            clearScreen();
            printTaskList(doingList);
            if(doingList->next != NULL){
                printf("Insert the task ID you want to change admin\n\n   => ");
                scanf("%d", &taskId);
                while(1){
                    if(taskIn(doingList,taskId) == 1){
                        changePerson(creationDateList, taskId);
                        saveInFile("doing", doingList);
                        printf("\nAdmin changed\nReturning to main menu...\n");
                        break;
                    }
                    else{
                        printf("\nNo task with that ID, try again\n   => ");
                        scanf("%d", &taskId);
                    }
                }
            }
            else{
                printf("No tasks on the Doing list\nReturning to main menu...\n");
            }
            sleep(3);
            break;
        case 8: //Done para TODO
            clearScreen();
            if(emptyTaskList(doneList) == 0){
                printTaskList(doneList);
                printf("Insert the task ID you want to transfer to ToDo\n\n   => ");
                scanf("%d", &taskId);
                assignDoneTodo(doneList, todoList, taskId);

                saveInFile("todo", todoList);
                //saveInFile("done", doneList);

            }
            else {
                printf("Empty list\n\nNo Tasks on the Done list\nReturning to main menu...\n");
                sleep(3);
            }
            break;
        case 9: //Visualizar todas as tarefas de uma pessoa. 
            clearScreen();
            /*
             if(creationDateList->next == NULL){
                printf("No tasks to display \nReturning to main menu...\n");
                sleep(3);
            }
             else{*/
                printf("Insert the admin you want to search\n\n   => ");
                scanf("%s", name);
                getchar();
                //tasksByName(todoList,name); não tem pessoa atribuída ho? porque pedir visualizar por fase do pipeline
                printf("------------- DOING LIST ------------\n");
                tasksByPerson(doingList,name);
                printf("------------- DONE LIST ------------\n");
                tasksByPerson(doneList,name);

            //sleep(3);
            printf("Press ENTER to proceed\n");
            getchar();
            break;
        case 10: //Listar ToDO
            clearScreen();
            printTaskList(todoList);
            printf("Press ENTER to proceed\n");
            getchar();
            break;
        case 11: //Listar DOING
            clearScreen();
            printTaskList(doingList);
            printf("Press ENTER to proceed\n");
            getchar();
            break;
        case 12: //Listar DONE
            clearScreen();
            printTaskList(doneList);
            printf("Press ENTER to proceed\n");
            getchar();
            break;
        case 13: //Print Board
            clearScreen();
            printBoard(todoList, doingList, doneList);
            printf("Press ENTER to proceed\n");
            getchar();
            break;
        case 20: //testing
            // creationDateList=fileToTasks("creation");
            // todoList=fileToTasks("todo");
            //fileToTasks("doing");
            // doneList=fileToTasks("done");
            //printf("\n\nLasIDList:%d   TASKS_ID:%d\n\n", creationDateList->lastID, TASKS_ID);
            getchar();
            break;
        case 30:
            clearFile("creation");
            clearFile("todo");
            clearFile("doing");
            clearFile("done");
            printf("\n <====== Files Cleared ======>\n");
            getchar();
        default:
            break;
    }
}

void storeLists(){
    if(emptyTaskList(creationDateList) != 1)saveInFile("creation", creationDateList);
    if(emptyTaskList(todoList) != 1)saveInFile("todo", todoList);
    if(emptyTaskList(doingList) != 1)saveInFile("doing", doingList);
    if(emptyTaskList(doneList) != 1)saveInFile("done", doneList);

    printf("\nFiles saved, exiting...\n");
    sleep(2);
}

void generateEmptyFiles(){
    if(!(FileExists("creation"))){
        CreateFile("creation");
    }
    if(!(FileExists("todo"))){
        CreateFile("todo");
    }
    if(!(FileExists("doing"))){
        CreateFile("doing");
    }
    if(!(FileExists("done"))){
        CreateFile("done");
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

    generateEmptyFiles();

    doingList=fileToTasks("doing");

    todoList=fileToTasks("todo");
    
    doneList=fileToTasks("done");

    creationDateList=fileToTasks("creation");

    while (option != 0){
        clearScreen();

        banner();

        printf("Behold the glorious menu \n\nPlease, select one of following options:\n\n");

        printf("1) Create new task\n2) Delete task\n3) List tasks\n4) Start Doing task\n5) Return task to To Do\n6) Mark task as Done\n7) Change admin of a Doing task\n8) Reopen Task\n9) Search all tasks by admin\n10) List To Do\n11) List Doing\n12) List Done\n13) List Kanban Board\n30) Clear All Files\n\n0) Exit\n\n   => ");

        scanf("%d", &option);
        getchar();

        menu(option);
    }

    storeLists();
    clearScreen();
    return 0;
}