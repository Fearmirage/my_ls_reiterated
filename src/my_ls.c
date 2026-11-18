#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

#include "my_ls.h"
#include "utils.h"
#include "get_files.h"

void ls(char* filename,int dot,int sort_by_modified){
    // ** // Getting contents
    int len = get_num_of_files(filename,dot);
    struct dirent** all_files = get_all_files(filename,len,dot);
    all_files = sort_files(all_files,len,filename,sort_by_modified);

    // ** // Printing contents
    for(int i = 0;i < len; i++){
        printf("%s\n",all_files[i]->d_name);
    }

    // ** // Freeing memory
    free(all_files);
}