#include <stdio.h>
#include <stdlib.h>
#include "kanban.c"



int main(){
    int option;

    printf("\e[1;1H\e[2J");

    printf("O nosso projeto em C para Laboratorio de Programacao\n");

    printf("Behold the glorious menu \n\nPlease, select one of following options:\n\n");

    printf("1) Create new list\n 2) Load previous list\n\n");

    scanf("%d", &option);

    return 0;
}