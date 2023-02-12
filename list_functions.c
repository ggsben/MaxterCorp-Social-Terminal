#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structures.h"
#include "econio.h"
#include "list_functions.h"



LinkNode *load_userbase(char *file, int count){

    int len;
    char filename[21+5];
    User *loaduser;
    Address *loadadd;
    LinkNode *head = NULL;
    LinkNode **current = &head;
    FILE* ub; //Userbase
    FILE* us; //Current user

    ub = fopen(file, "r");
    /*if(ub == NULL) {
        perror("Error opening file");
        return(-1);
    }*/

    for(int i = 0; i < count; i++){
        fgets(filename, 21+5, ub);

        len = strlen(filename);
        if(filename[len-1] == '\n' ){
            filename[len-1] = '\0';
        }

        *current = (LinkNode*)malloc(sizeof(LinkNode));
        if(*current == NULL) {
            perror("Error allocating memory");
            return(-1);
        }

        if(*current){
            loaduser = (User*)malloc(sizeof(User));
            loadadd = (Address*)malloc(sizeof(Address)-1);
            us = fopen(filename, "r");
            fgets(loaduser->Username, 22, us);
            fgets(loaduser->Password, 22, us);
            fgets(loaduser->Name, 52, us);
            fgets(loaduser->Sex, 8, us);
            fgets(loaduser->Birth, 14, us);

            fgets(loadadd->country, 52, us);
            fgets(loadadd->city, 52, us);
            fgets(loadadd->street, 52, us);
            fgets(loadadd->house, 6, us);


            fgets(loaduser->Phonenumber, 15, us);
            fgets(loaduser->School, 52, us);
            fgets(loaduser->Work, 52, us);
            fclose(us);
            (*current)->loaded = loaduser;
            (*current)->loaded->Useraddress = loadadd;
            (*current)->next = NULL;
            current = &(*current)->next;
        }
    }

    return head;
}

void free_list(LinkNode *first){
    LinkNode *p;

    while (first != NULL)
    {
        p = first;
        first = first->next;
        free(p);
    }
}
