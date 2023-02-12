#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "structures.h"
#include "econio.h"
#include "formatting_functions.h"

void remove_n(char *str){
    int len = 0;
    len = strlen(str);
    if(str[len-1] == '\n' ){
        str[len-1] = '\0';
    }
}
