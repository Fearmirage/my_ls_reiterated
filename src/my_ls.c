#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

#include "my_ls.h"
#include "get_files.h"

int simple_ls(char* dirname,int dot,int sort_by_modified){
    // ** // Getting contents
    int len = get_num_of_files(dirname,dot);
    if(len == -1){
        return 1;
    }
    struct dirent** all_files = get_all_files(dirname,len,dot);
    if(all_files == NULL){
        return 1;
    }
    all_files = sort_files(all_files,len,dirname,sort_by_modified);

    // ** // Printing contents
    for(int i = 0;i < len; i++){
        printf("%s\n",all_files[i]->d_name);
    }

    // ** // Freeing memory
    free(all_files);
    return 0;
}
int* get_options(int argc, char** argv){
    int* option_values = malloc(sizeof(int)*2);

    for(int i = 1; i < argc;i++){
        if (*argv[i] == '-') {
            argv[i]++;
            while(*argv[i] != 0){
                if(*argv[i] == 'a') {
                    option_values[0] = 1;
                }else if(*argv[i] == 't'){
                    option_values[1] = 1;
                }else if(i == 1){
                    printf("Error : option that isn't supported was specified\n");
                    option_values[0] = -1;
                    return option_values;
                }
                argv[i]++;
            }
        }
    }
    return option_values;
}
int get_paths(int argc,char** argv,char* paths_arr[]){
    int path_count = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-' && argv[i][0] != '\0') {
            paths_arr[path_count++] = argv[i];
        }
    }
    if(path_count > 1){
        sort_paths(paths_arr,path_count);
    }
    return path_count;
}
int ls_on_all_paths(int* options,char** paths,int path_count){
    int did_ls_at_least_once = 0;
    for(int i = 0; i < path_count; i++){
        did_ls_at_least_once = 1;
        char* dirname = paths[i];
        if (path_count > 1){
            printf("%s:\n", dirname);
        }
        simple_ls(dirname, options[0], options[1]);

        if(i != path_count - 1){
            printf("\n");
        }
    }
    return did_ls_at_least_once;
}
int list(int argc,char** argv){
    int* options = get_options(argc,argv);
    if(options[0] == -1){
        return 1;
    }
    char* paths[argc];
    int path_count = get_paths(argc,argv,paths);

    int did_ls_at_least_once = ls_on_all_paths(options,paths,path_count);
    if (!did_ls_at_least_once){
        simple_ls("./",options[0], options[1]);
    }
    free(options);
    return 0;
}