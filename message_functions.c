#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structures.h"
#include "econio.h"
#include "message_functions.h"




void messages(int messagecount, int usercount, User *current){

    int choice = 0;

    econio_clrscr();
    printf("[1]Read messages\n[2]Send messages\n[3]Back\n");
    scanf("%d", &choice);

    switch(choice){
    case 1:
        read_message(usercount, messagecount, current);
        break;
    case 2:
        send_message(messagecount, usercount);
        break;
    case 3:
        break;
    default:
        econio_clrscr();
        printf("Input should be index of desired option!\n");
        getchar();
        getchar();
        econio_clrscr();
    }

}

void read_message(int usercount, int messagecount, User *current){

    int size = 0;
    int mcount = 0;
    char search[21+13];
    char temp[21+13];
    FILE *mess;

    strcpy(search, current->Username);
    remove_n(search);
    strcat(search, "MESSAGE");

    econio_clrscr();
    for(int iter = 0; iter < messagecount; iter++){
        sprintf(temp, "%s%d.txt", search, iter);
        mess = fopen(temp, "r");

        int count = 0;
        if(mess != NULL){
            mcount++;
            char c;
            char sender[51];
            fgets(sender, 51, mess);
            remove_n(sender);
            printf("Message #%d from %s: ", mcount, sender);
            while(c != '\n')
            {
                c = fgetc(mess);
                printf("%c", c);
            }
            c = fgetc(mess);

        }


    }
    getchar();
    getchar();
}

void send_message(int messagecount, int usercount){

    char messagename[21+8] = "", c, *text = "", adressee[51] = "", sender[51] = "";
    int i = 0, j = 1;
    LinkNode *users = NULL, *head = NULL;
    FILE *message, *mc;

    econio_clrscr();
    text = (char*)malloc(sizeof(char));
    if(text == NULL) {
        perror("Error allocating memory");
        return(-1);
    }
    getchar();

    printf("Enter name of addressee:\n");
    fgets(adressee, 51, stdin);
    printf("Enter your name:\n");
    fgets(sender, 51, stdin);
    printf("Enter message:\n");

    while (c != '\n') {
        c = getc(stdin);
        text = (char*)realloc(text, j * sizeof(char));
        text[i] = c;

        i++;
        j++;
    }

    users = load_userbase("userlist.txt", usercount);
    head = users;
    while(strcmp(head->loaded->Name, adressee) != 0){
        head = head->next;
    }

    strcpy(adressee, head->loaded->Username);
    remove_n(adressee);
    strcat(adressee, "MESSAGE");

    sprintf(messagename, "%s%d.txt", adressee, messagecount);

    message = fopen(messagename, "w");
    fprintf(message, sender);
    fprintf(message, text);
    fclose(message);

    mc = fopen("messagecount.txt", "w+");
    fprintf(mc, "%d", messagecount+1);
    fclose(mc);
}
