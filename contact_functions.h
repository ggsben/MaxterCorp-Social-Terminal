#ifndef CONTACT_FUNCTIONS_H_INCLUDED
#define CONTACT_FUNCTIONS_H_INCLUDED

void add_contact(char *file, char *filename, int state);

void check_contact(char *filename, int state);

void search(LinkNode *first, int usercount, User *current, LinkNode *result, char *filename);

char* check_info(int idx, LinkNode *list, int state);

#endif // CONTACT_FUNCTIONS_H_INCLUDED
