#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structures.h"
#include "econio.h"
#include "user_functions.h"

bool registration(){

    User *newuser;
    Address *newadd;
    char login[21], name[26], surname[26], *filename;
    FILE* check; //Used to check if username is taken
    FILE* fp;
    FILE* userlist; //File containing every user data files' name

    newuser = (User*)malloc(sizeof(User));
    if(newuser == NULL) {
        perror("Error allocating memory");
        return(-1);
    }

    newadd = (Address*)malloc(sizeof(Address));
    if(newadd == NULL) {
        perror("Error allocating memory");
        return(-1);
    }

    printf("Thank you for choosing MaxterCorp! To register, first you need a Login Name!\nConsult the manual regarding formatting!\n");
    scanf("%s", newuser->Username);

    filename = (char*) malloc((strlen(newuser->Username) + 5) * sizeof(char));
    if(filename == NULL) {
        perror("Error allocating memory");
        return(-1);
    }

    strcpy(filename, newuser->Username);
    strcat(filename, ".txt");
    check = fopen(filename, "r");
    if(check != NULL){
        econio_clrscr();
        printf("Username taken, please try a different one!");
        getchar();
        getchar();
        return;
    }
    fclose(check);
    fp = fopen(filename, "w");
    if(fp == NULL) {
        perror("Error opening file");
        return(-1);
    }

    printf("\nNow select a password!\n");
    scanf("%s", newuser->Password);

    printf("\nPlease fill in your name.\n");
    scanf("%s %s", &name, &surname);
    strcpy(newuser->Name, name);
    strcat(newuser->Name, " ");
    strcat(newuser->Name, surname);

    printf("\nPlease fill in your info. Refer to the manual regarding format!\nSex, birth date, phone number, school, work place, address (country, city, street, house number).\nWrite none if you wish for something to stay hidden!\n\n");
    scanf("%s", newuser->Sex);
    scanf("%s", newuser->Birth);
    scanf("%s", newuser->Phonenumber);
    scanf("%s", newuser->School);
    scanf("%s", newuser->Work);
    scanf("%s", newadd->country);
    scanf("%s", newadd->city);
    scanf("%s", newadd->street);
    scanf("%s", newadd->house);
    newuser->Useraddress = newadd;

    fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", newuser->Username, newuser->Password, newuser->Name, newuser->Sex, newuser->Birth, newuser->Useraddress->country, newuser->Useraddress->city, newuser->Useraddress->street, newuser->Useraddress->house, newuser->Phonenumber, newuser->School, newuser->Work);
    fclose(fp);

    userlist = fopen("userlist.txt", "a");
    fprintf(userlist, "%s\n", filename);
    fclose(userlist);

    econio_clrscr();
    printf("Congratulations! You have successfully registered!\nYou are now able to login.\n");
    getchar();
    getchar();

    free(newuser);
    free(newadd);
    free(filename);

    return true;
}

char* login(bool *loggedon){

    econio_clrscr();
    char *filename;
    char current;
    char temp[21];
    char input[21];
    bool search = true;
    char username[25], password[25];
    int line = 0;
    FILE* id;

    printf("Username: ");
    scanf("%s", &username);
    printf("Password: ");
    scanf("%s", &password);

    filename = (char*)malloc((strlen(username) + 5) * sizeof(char));
    if(filename == NULL) {
        perror("Error allocating memory");
        return(-1);
    }
    strcpy(filename, username);
    strcat(filename, ".txt");

    id = fopen(filename, "r+");
    if(id == NULL) {
        perror("Error opening file");
        return(-1);
    }

    fgets(temp, 21, id);
    fgets(input, 21, id);
    strtok(input, "\n");

    if(strcmp(password, input) == 0){
        *loggedon = true;
        return filename;
    }

    free(filename);

    return NULL;
}

void infoedit(char *filename){
    User *edit;
    int choice;
    Address *editaddress;
    FILE *id, *edited;
    printf("%s", filename);

    edit = (User*)malloc(sizeof(User));
    editaddress = (Address*)malloc(sizeof(Address));
    id = fopen(filename, "r+");
    if(id == NULL) {
        perror("Error opening file");
        return(-1);
    }

    fgets(edit->Username, 22, id);
    fgets(edit->Password, 22, id);
    fgets(edit->Name, 52, id);
    fgets(edit->Sex, 8, id);
    fgets(edit->Birth, 14, id);

    fgets(editaddress->country, 52, id);
    fgets(editaddress->city, 52, id);
    fgets(editaddress->street, 52, id);
    fgets(editaddress->house, 6, id);
    edit->Useraddress = editaddress;

    fgets(edit->Phonenumber, 15, id);
    fgets(edit->School, 52, id);
    fgets(edit->Work, 52, id);
    fclose(id);

    do{
    econio_clrscr();
    printf("What would you like to edit?\n");
    printf("[1]Password\n[2]Name: %s[3]Sex: %s[4]Birth date: %s[5]Address\n[6]Phone number: %s[7]School: %s[8]Work: %s\n[9]Back\n", edit->Name, edit->Sex, edit->Birth, edit->Phonenumber, edit->School,edit->Work);
    choice = 0;
    scanf("%d", &choice);

        switch(choice){
        case 1:
            econio_clrscr();
            printf("What should it be changed to?\n");
            scanf("%s", &edit->Password);
            strcat(edit->Password, "\n");
            break;
        case 2:
            econio_clrscr();
            printf("What should it be changed to?\n");
            getchar();
            scanf("%[^\n]s", &edit->Name);
            strcat(edit->Name, "\n");
            break;
        case 3:
            econio_clrscr();
            printf("What should it be changed to?\n");
            scanf("%s", &edit->Sex);
            strcat(edit->Sex, "\n");
            break;
        case 4:
            econio_clrscr();
            printf("What should it be changed to?\n");
            scanf("%s", &edit->Birth);
            strcat(edit->Birth, "\n");
            break;
        case 5:
            econio_clrscr();
            printf("[1]Country\n[2]City\n[3]Street\n[4]House\n[5]Back\n");
            scanf("%d", &choice);
                switch(choice){
                case 1:
                    econio_clrscr();
                    printf("What should it be changed to?\n");
                    scanf("%s", &edit->Useraddress->country);
                    strcat(edit->Useraddress->country, "\n");
                    break;
                case 2:
                    econio_clrscr();
                    printf("What should it be changed to?\n");
                    scanf("%s", &edit->Useraddress->city);
                    strcat(edit->Useraddress->city, "\n");
                case 3:
                    econio_clrscr();
                    printf("What should it be changed to?\n");
                    scanf("%s", &edit->Useraddress->street);
                    strcat(edit->Useraddress->street, "\n");
                    break;
                case 4:
                    econio_clrscr();
                    printf("What should it be changed to?\n");
                    scanf("%s", &edit->Useraddress->house);
                    strcat(edit->Useraddress->house, "\n");
                    break;
                case 5:
                    break;
                default:
                    econio_clrscr();
                    printf("Input should be index of desired option!\n");
                    getchar();
                    getchar();
                    econio_clrscr();
            }
            break;
        case 6:
            econio_clrscr();
            printf("What should it be changed to?\n");
            scanf("%s", &edit->Phonenumber);
            strcat(edit->Phonenumber, "\n");
            break;
        case 7:
            econio_clrscr();
            printf("What should it be changed to?\n");
            getchar();
            scanf("%[^\n]s", &edit->School);
            strcat(edit->School, "\n");
            break;
        case 8:
            econio_clrscr();
            printf("What should it be changed to?\n");
            getchar();
            scanf("%[^\n]s", &edit->Work);
            strcat(edit->Work, "\n");
            break;
        case 9:
            break;
        default:
            econio_clrscr();
            printf("Input should be index of desired option!\n");
            getchar();
            getchar();
            econio_clrscr();
        }
    }while(choice != 9);

        edited = fopen(filename, "w");
        if(edited == 0){
            perror("Error opening file");
            return(-1);
        }
        fprintf(edited, "%s%s%s%s%s%s%s%s%s%s%s%s", edit->Username, edit->Password, edit->Name, edit->Sex, edit->Birth, edit->Useraddress->country, edit->Useraddress->city, edit->Useraddress->street, edit->Useraddress->house, edit->Phonenumber, edit->School, edit->Work);
        fclose(edited);

}
