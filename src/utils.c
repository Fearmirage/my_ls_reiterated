#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

#include "utils.h"

//memcpy, strlen, strcat, strcmp
int my_strlen(char* string){
    char* pointer = string;
    while(*pointer != 0){
        pointer++;
    }
    return pointer-string;
}

char* my_strcat(char* dst, char* src){
    //Find the end (\0) of dst
    char* dst_ptr = dst;
    while(*dst_ptr){
        dst_ptr++;
    }
    //Append src
    char* src_ptr = src;
    while(*src_ptr){
        *dst_ptr = *src_ptr;
        dst_ptr++;
        src_ptr++;
    }

    *dst_ptr = '\0';
    return dst;
}

DIR* safe_opendir(char* file_name){
    DIR* dir = opendir(file_name);
    if (dir == NULL) {
        printf("Cannot open directory '%s'\n", file_name);
        exit(1);
    }
    return dir;
}