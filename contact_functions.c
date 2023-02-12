#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structures.h"
#include "econio.h"
#include "contact_functions.h"

void add_contact(char *file, char *filename, int state){

    int choice = 0;
    int count = 0;
    int idx = 0;
    char str[51];
    char temp[51] = "", temp2[51] = "";
    char *contactfilename;
    User *read;
    Address *readadd;
    LinkNode *list = NULL;
    LinkNode *head = NULL;
    FILE* result;
    FILE* contacts;

    contactfilename = (char*)malloc(sizeof(char)*strlen(filename) + 5);
    strcpy(contactfilename, "c");
    strcat(contactfilename, filename);

    read = (User*)malloc(sizeof(User));
    result = fopen(file, "r");
    while(fgets(str, 51, result) != 0){
        count++;
    }

    list = load_userbase(file, count);
    econio_clrscr();
    printf("Who would you like to add?\n\n");

    for(head = list; head != NULL; head = head->next){
        idx++;
        printf("[%d]%s", idx, head->loaded->Name);
    }

    scanf("%d", &choice);
    strcpy(temp, check_info(choice-1, list, state));
    printf("\n\nAdd as contact?\n[1]Yes\n[2]No\n");
    scanf("%d", &choice);
    switch(choice){
    case 1:

        contacts = fopen(contactfilename, "r");
        strcpy(temp2, temp);
        remove_n(temp2);
        strcat(temp2, ".txt\n");
        while(fgets(str, 51, contacts) != 0){
            if(strcmp(str, temp2) == 0){
                printf("They are already your contact!");
                getchar();
                getchar();
                fclose(contacts);
                free(read);
                free_list(list);
                free(contactfilename);
                fclose(result);
                return;
            }
        }

        contacts = fopen(contactfilename, "a");
        remove_n(temp);
        fprintf(contacts, "%s.txt\n", temp);
        fclose(contacts);
        break;
    case 2:
        break;
    }
    free(read);
    free_list(list);
    free(contactfilename);
    fclose(result);
}

void check_contact(char *filename, int state){

    int idx = 0;
    int count = 0;
    int choice = 0;
    char str[51];
    char *contactfilename;
    User *read;
    FILE* contact;
    LinkNode *list = NULL;
    LinkNode *head = NULL;

    read = (User*)malloc(sizeof(User));


    contactfilename = (char*)malloc(sizeof(char)*(strlen(filename) + 1));
    strcpy(contactfilename, "c");
    strcat(contactfilename, filename);

    contact = fopen(contactfilename, "r");
    while(fgets(str, 51, contact) != 0){
        count++;
    }
    list = load_userbase(contactfilename, count);

    if(list == NULL){
        printf("They have no contacts yet.\n\n");
    }

    while(choice != idx+1){
        choice = 0;
        idx = 0;
        for(head = list; head != NULL; head = head->next){
            idx++;
            printf("[%d]%s", idx, head->loaded->Name);
        }
        printf("[%d]Continue\n", idx+1);

            scanf("%d", &choice);
            if(choice > idx+1 || choice <= 0){
                econio_clrscr();
                printf("Input should be index of desired option!\n");
                getchar();
                getchar();
                choice = idx+1;
            }
            if(state == 0){
                if(choice != idx+1){
                    check_info(choice-1, list, 0);
                    printf("\n");
                    getchar();
                    getchar();
            }
        }
    }
    fclose(contact);
    free_list(list);
    free_list(head);
}

void search(LinkNode *first, int usercount, User *current, LinkNode *result, char *filename){

    int choice, idx, len;
    char str[51], temp[51];
    User *userfound;
    FILE* rs;

    rs = fopen("result.txt", "w");
    if(rs == NULL) {
        perror("Error opening file");
        return(-1);
    }

    result = (LinkNode*)malloc(sizeof(LinkNode));
    result->next = NULL;
    userfound = (User*)malloc(sizeof(User));
    result->loaded = userfound;

    if(result == NULL){
        perror("Error allocating memory");
        return(-1);
    }

    do{

        choice = 0;
        idx = 1;
        LinkNode *head = first;
        econio_clrscr();
        printf("What would you like to search based on?\n\n[1]Name\n[2]Sex\n[3]Country\n[4]City\n[5]School\n[6]Work\n[7]Add contacts from results\n[8]Back\n");
        scanf("%d", &choice);
        switch(choice){
        case 1:
            econio_clrscr();
            printf("Name to search for:\n");
            getchar();
            fgets(str, 51, stdin);
            strcpy(temp, str);
            for(int i = 1; i <= usercount; i++){
                if(strcmp(head->loaded->Name, str) == 0 && strcmp(head->loaded->Username, current->Username) != 0){
                    len = 0;
                    printf("[%d]%s", idx, head->loaded->Name);
                    sprintf(temp, "%s", head->loaded->Username);
                    remove_n(&temp);
                    fprintf(rs, "%s.txt\n", temp);
                    idx++;

                }
                head = head->next;
            }
            if(idx == 1){
                printf("No user found!");
            }
            getchar();
            break;
        case 2:
            econio_clrscr();
            printf("What sex:\n");
            getchar();
            fgets(str, 8, stdin);
            strcpy(temp, str);
            for(int i = 1; i <= usercount; i++){
                if(strcmp(head->loaded->Sex, str) == 0 && strcmp(head->loaded->Username, current->Username) != 0){
                    len = 0;
                    printf("[%d]%s", idx, head->loaded->Name);
                    sprintf(temp, "%s", head->loaded->Username);
                    remove_n(&temp);
                    fprintf(rs, "%s.txt\n", temp);
                    idx++;
                }
                head = head->next;
            }
            if(idx == 1){
                printf("No user found!");
            }
            getchar();
            break;
        case 3:
            econio_clrscr();
            printf("What country:\n");
            getchar();
            fgets(str, 51, stdin);
            strcpy(temp, str);
            for(int i = 1; i <= usercount; i++){
                if(strcmp(head->loaded->Useraddress->country, str) == 0 && strcmp(head->loaded->Username, current->Username) != 0){
                    len = 0;
                    printf("[%d]%s", idx, head->loaded->Name);
                    sprintf(temp, "%s", head->loaded->Username);
                    remove_n(&temp);
                    fprintf(rs, "%s.txt\n", temp);
                    idx++;
                }
                head = head->next;
            }
            if(idx == 1){
                printf("No user found!");
            }
            getchar();
            break;
        case 4:
            econio_clrscr();
            printf("What city:\n");
            getchar();
            fgets(str, 51, stdin);
            strcpy(temp, str);
            for(int i = 1; i <= usercount; i++){
                if(strcmp(head->loaded->Useraddress->city, str) == 0 && strcmp(head->loaded->Username, current->Username) != 0){
                    len = 0;
                    printf("[%d]%s", idx, head->loaded->Name);
                    sprintf(temp, "%s", head->loaded->Username);
                    remove_n(&temp);
                    fprintf(rs, "%s.txt\n", temp);
                    idx++;
                }
                head = head->next;
            }
            if(idx == 1){
                printf("No user found!");
            }
            getchar();
            break;
        case 5:
            econio_clrscr();
            printf("What school:\n");
            getchar();
            fgets(str, 51, stdin);
            strcpy(temp, str);
            for(int i = 1; i <= usercount; i++){
                if(strcmp(head->loaded->School, str) == 0 && strcmp(head->loaded->Username, current->Username) != 0){
                    len = 0;
                    printf("[%d]%s", idx, head->loaded->Name);
                    sprintf(temp, "%s", head->loaded->Username);
                    remove_n(&temp);
                    fprintf(rs, "%s.txt\n", temp);
                    idx++;
                }
                head = head->next;
            }
            if(idx == 1){
                printf("No user found!");
            }
            getchar();
            break;
        case 6:
            econio_clrscr();
            printf("What work:\n");
            getchar();
            fgets(str, 51, stdin);
            strcpy(temp, str);
            for(int i = 1; i <= usercount; i++){
                if(strcmp(head->loaded->Work, str) == 0 && strcmp(head->loaded->Username, current->Username) != 0){
                    len = 0;
                    printf("[%d]%s", idx, head->loaded->Name);
                    sprintf(temp, "%s", head->loaded->Username);
                    remove_n(&temp);
                    fprintf(rs, "%s.txt\n", temp);
                    idx++;
                }
                head = head->next;
            }
            if(idx == 1){
                printf("No user found!");
            }
            getchar();
            break;
        case 7:
            fclose(rs);
            add_contact("result.txt", filename, 1);
            break;
        case 8:
            break;
        default:
            econio_clrscr();
            printf("Input should be index of desired option!\n");
            getchar();
            getchar();
            econio_clrscr();
        }
        free_list(head);
    }while(choice != 8);

    fclose(rs);
    free_list(result);
    free(userfound);


}

char* check_info(int idx, LinkNode *list, int state){

    char filename[51+5] = "";
    //strcpy(filename, "c");

    LinkNode *head = list;
    econio_clrscr();

    for(int i = 0; i < idx; i++){
        head = head->next;
    }
    strcpy(filename, head->loaded->Username);
    remove_n(&filename);
    strcat(filename, ".txt");
    printf("Name: %sSex: %sBirth date: %sCountry: %sCity: %sStreet: %sHouse: %sPhone number: %sSchool: %sWork: %s", head->loaded->Name, head->loaded->Sex, head->loaded->Birth, head->loaded->Useraddress->country, head->loaded->Useraddress->city, head->loaded->Useraddress->street, head->loaded->Useraddress->house, head->loaded->Phonenumber, head->loaded->School, head->loaded->Work);
    printf("\nTheir contacts are:\n\n");
    check_contact(filename, state);

    return head->loaded->Username;
}

