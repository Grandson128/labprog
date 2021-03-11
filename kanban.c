#include <stdio.h>
#include <stdlib.h>
#include "kanban.h"



Tasklist createTaskList(){
    Tasklist aux;
    aux = (Tasklist)malloc(sizeof(Node));
    if (aux != NULL) {
        aux->info = 0;
        aux->next = NULL;
    }
    return aux;

}

Tasklist removeTaskList (Tasklist list){
    Tasklist temp_ptr;

    while (lista_vazia(list) == 0){
        temp_ptr = list;
        list = list->next;
        free(temp_ptr);
    }
    free(list);
    return NULL;
}