#include <stdio.h>
#include <dirent.h>

#include "utils.h"

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

int my_strcmp(char* string1, char* string2){
    char* pointer1 = string1;
    char* pointer2 = string2;
    while (*pointer1 != '\0'){
        if (*pointer2 == '\0'){
            return -1;
        };
        pointer1++;
        pointer2++;
    };
    if (*pointer2 == '\0'){
        return 0;
    }else{
        return 1;
    }
}

DIR* safe_opendir(char* dirname){
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return NULL;
    }
    return dir;
}