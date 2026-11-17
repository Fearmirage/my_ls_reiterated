#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

#include "utils.h"

DIR* safe_opendir(char* file_name){
    DIR* dir = opendir(file_name);
    if (dir == NULL) {
        printf("Cannot open directory '%s'\n", file_name);
        exit(1);
    }
    return dir;
}