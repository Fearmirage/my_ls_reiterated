#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#include "utils.h"

int get_num_of_files(char* filename,int dot){
    DIR* dir = safe_opendir(filename);
    int len = 0;
    struct dirent* file = readdir(dir);
    while(file != NULL){
        if ( dot ||  *file->d_name != '.' ){
            len++;
        }
        file = readdir(dir);
    }
    closedir(dir);
    return len;
}

struct dirent** get_all_files(char* filename, int len,int dot){
    //get the amount of files
    DIR* dir = safe_opendir(filename);
    struct dirent** all_files = malloc(len*sizeof(struct dirent*));
    struct dirent* file = readdir(dir);
    int i = 0;
    while(file != NULL){
        if ( dot ||  *file->d_name != '.' ){
            all_files[i] = malloc(sizeof(struct dirent));
            memcpy(all_files[i], file, sizeof(struct dirent));
            i++;
        }
        file = readdir(dir);
    }
    closedir(dir);
    return all_files;
}

struct timespec get_when_last_modified(struct dirent* file1,char* parent_file){
    size_t size = strlen(parent_file) + 1 + strlen(file1->d_name) + 1;
    char* path = malloc(size);
    strcpy(path,parent_file);
    strcat(path,"/");
    strcat(path, file1->d_name);
    struct stat buffer;
    int status = stat(path,&buffer);
    if (status == -1){
        printf("[%d] Error while getting file meta data",status);
        exit(1);
    }
    free(path);
    return buffer.st_atimespec;
}

void sort_paths(char** paths,size_t path_count){
    //Insertion Sort
    char* key;
    size_t j;
    for(size_t i = 0; i<path_count; i++) {
        key = paths[i]; //take value
        j = i;
        while(j > 0 && strcmp(paths[j-1], key) > 0) {
            paths[j] = paths[j-1];
            j--;
        }
        paths[j] = key; //insert in right place
    }
}

int last_modif_compare(struct dirent* file1,struct dirent* file2,char* parent_file){
    struct timespec time_file1 = get_when_last_modified(file1,parent_file);
    struct timespec time_file2 = get_when_last_modified(file2,parent_file);
    if (time_file1.tv_sec != time_file2.tv_sec){
        return time_file1.tv_sec < time_file2.tv_sec;
    }else{
        return time_file1.tv_nsec < time_file2.tv_nsec;
    }
}

struct dirent** sort_files(struct dirent** files,int len,char* parent_file,int sort_by_modified){
    //Insertion Sort
    struct dirent* key;
    int j;
    for(int i = 1; i<len; i++) {
        key = files[i]; //take value
        j = i;
        if (sort_by_modified){
            while(j > 0 && last_modif_compare(files[j-1],key,parent_file)) {
                files[j] = files[j-1];
                j--;
            }
        }else{
            while(j > 0 && strcmp(files[j-1]->d_name, key->d_name) > 0) {
                files[j] = files[j-1];
                j--;
            }
        }

        files[j] = key; //insert in right place
    }
    return files;
}

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
    for (int i = 0; i < len; i++) {
        free(all_files[i]);
    }
    free(all_files);
}

int main(int argc,char** argv){
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
        ls(file_name, dot, sort_by_modified);

        if(i != path_count - 1){
            printf("\n");
        }
    }

    if (!did_ls_at_least_once){
        ls("./",dot,sort_by_modified);
    }
    return 0;
}

/* How to compare with ls:
$>./my_ls > my_ls.output
$>ls -1 > ls.output
$>diff my_ls.output ls.output
$>
*/