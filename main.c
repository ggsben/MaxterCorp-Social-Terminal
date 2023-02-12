#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structures.h"
#include "econio.h"
#include "user_functions.h"
#include "contact_functions.h"
#include "formatting_functions.h"
#include "list_functions.h"
#include "message_functions.h"
#include "user_functions.h"


int main(){

    int choice;
    int usercount = 0;
    int messagecount = 0;
    bool loggedon = false;
    bool success = false;
    char temp[21];
    char *filename = NULL;
    User *current = NULL;
    Address *currentadd;
    LinkNode *first = NULL;
    LinkNode *result = NULL;
    FILE* id;
    FILE* uc;
    FILE *mc;

    uc = fopen("usercount.txt", "r");
    if(uc == NULL){
        uc = fopen("usercount.txt", "w+");
        fprintf(uc, "%d", usercount);
    }
    else{
        fscanf(uc,"%d", &usercount);
    }
    fclose(uc);

    mc = fopen("messagecount.txt", "r");
    if(mc == NULL){
        mc = fopen("messagecount.txt", "w+");
        fprintf(mc, "%d", messagecount);
    }
    else{
        fscanf(mc,"%d", &messagecount);
    }
    fclose(uc);

    LOOP:do {
        econio_clrscr();
        printf("Welcome to the MaxterCorp Social Terminal!\nPlease make a choice:\n\n[1] Login\n[2] Register\n[3] Exit\n\nUsercount: %d\n", usercount);
        scanf("%d", &choice);

        switch(choice){
        case 1:
            filename = login(&loggedon);
            if(filename == NULL){
                econio_clrscr();
                printf("Wrong username or password!");
                getchar();
                getchar();
            }
            break;
        case 2:
            econio_clrscr();
            success = registration();
            if(success == true){
                usercount++;
            }
            success = false;
            econio_clrscr();
            break;
        case 3:
            uc = fopen("usercount.txt", "w");
            fprintf(uc, "%d", usercount);
            fclose(uc);
            exit(0);
            break;
        default:
            econio_clrscr();
            printf("Input should be index of desired option!\n");
            getchar();
            getchar();
            econio_clrscr();
        }
    } while(loggedon != true);

    econio_clrscr();

    current = (User*)malloc(sizeof(User));
    currentadd = (Address*)malloc(sizeof(Address));
    id = fopen(filename, "r+");

    printf("You have successfully logged into your account! You can now access your personal information.\n");
    getchar();
    getchar();

    fgets(current->Username, 21, id);
    fgets(temp, 21, id);
    fgets(current->Name, 51, id);

    do {
        econio_clrscr();
        printf("Current User: %s", current->Name);
        printf("\n[1]Check your contacts\n[2]Search for contacts\n[3]Add contacts\n[4]Edit info\n[5]Messages\n[6]Logout\n");
        scanf("%d", &choice);

        switch(choice){
        case 1:
            econio_clrscr();
            printf("Your contacts are:\n\n");
            check_contact(filename, 0);
            break;
        case 2:
            first = load_userbase("userlist.txt", usercount);
            search(first, usercount, current, result, filename);
            break;
        case 3:
            add_contact("userlist.txt", filename, 1);
            break;
        case 4:
            infoedit(filename);
            break;
        case 5:
            messages(messagecount, usercount, current);
            break;
        case 6:
            loggedon = false;
            free(current);
            free(currentadd);
            free(filename);
            break;
        default:
            econio_clrscr();
            printf("Input should be index of desired option!\n");
            getchar();
            getchar();
            econio_clrscr();
        }
    } while(loggedon != false);
    goto LOOP;



    return 0;
}
