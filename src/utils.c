#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

#include "utils.h"

//memcpy, strlen, strcat, strcpy, strcmp
int my_strlen(char* string){
    char* pointer = string;
    while(*pointer != 0){
        pointer++;
    }
    return pointer-string;
}

DIR* safe_opendir(char* file_name){
    DIR* dir = opendir(file_name);
    if (dir == NULL) {
        printf("Cannot open directory '%s'\n", file_name);
        exit(1);
    }
    return dir;
}