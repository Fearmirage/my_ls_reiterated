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
int list(int argc,char** argv){
    int dot = 0;
    int sort_by_modified = 0;

    for(int i = 1; i < argc;i++){
        if (*argv[i] == '-') {
            argv[i]++;
            while(*argv[i] != 0){
                if(*argv[i] == 'a') {
                    dot = 1;
                }else if(*argv[i] == 't'){
                    sort_by_modified = 1;
                }else if(i == 1){
                    printf("Error : option that isn't supported was specified\n");
                    return 1;
                }
                argv[i]++;
            }
        }
    }

    char* paths[argc];
    int path_count = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-' && argv[i][0] != '\0') {
            paths[path_count++] = argv[i];
        }
    }
    if(path_count > 1){
        sort_paths(paths,path_count);
    }


    int did_ls_at_least_once = 0;

    for(int i = 0; i < path_count; i++){
        did_ls_at_least_once = 1;
        char* file_name = paths[i];
        if (path_count > 1){
            printf("%s:\n", file_name);
        }
        simple_ls(file_name, dot, sort_by_modified);

        if(i != path_count - 1){
            printf("\n");
        }
    }

    if (!did_ls_at_least_once){
        simple_ls("./",dot,sort_by_modified);
    }
    return 0;
}