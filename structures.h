#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED

typedef struct Address{
    char country[51];
    char city[51];
    char street[51];
    char house[5];
} Address;

typedef struct User{
    char Username[21];
    char Password[21];
    char Name[51];
    char Sex[8];
    char Birth[13];
    Address *Useraddress;
    char Phonenumber[14];
    char School[51];
    char Work[51];
} User;

/*typedef struct Message{
    char Sender[21];
    char *Text;
} Message;*/

typedef struct LinkNode{
    User *loaded;
    struct LinkNode *next;
} LinkNode;



#endif // STRUCTURES_H_INCLUDED
