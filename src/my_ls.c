#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

#include "my_ls.h"
#include "utils.h"
#include "get_files.h"

void simple_ls(char* dirname,int dot,int sort_by_modified){
    // ** // Getting contents
    int len = get_num_of_files(dirname,dot);
    struct dirent** all_files = get_all_files(dirname,len,dot);
    all_files = sort_files(all_files,len,dirname,sort_by_modified);

    // ** // Printing contents
    for(int i = 0;i < len; i++){
        printf("%s\n",all_files[i]->d_name);
    }

    // ** // Freeing memory
    free(all_files);
}