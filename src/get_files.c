#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "get_files.h"
#include "utils.h"

int get_num_of_files(char* dirname,int dot){
    DIR* dir = safe_opendir(dirname);
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

struct dirent** get_all_files(char* dirname, int len,int dot){
    //get the amount of files
    DIR* dir = safe_opendir(dirname);
    struct dirent** all_files = malloc(len*sizeof(struct dirent*));
    struct dirent* file = readdir(dir);
    int i = 0;
    while(file != NULL){
        if ( dot ||  *file->d_name != '.' ){
            all_files[i] = file;
            i++;
        }
        file = readdir(dir);
    }
    closedir(dir);
    return all_files;
}

struct timespec get_when_last_modified(struct dirent* file1,char* parent_file){
    size_t size = my_strlen(parent_file) + 1 + my_strlen(file1->d_name) + 1;
    char* path = malloc(size);
    path[0] = '\0';
    my_strcat(path, parent_file); my_strcat(path, "/"); my_strcat(path, file1->d_name);
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
        while(j > 0 && my_strcmp(paths[j-1], key) > 0) {
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
            while(j > 0 && my_strcmp(files[j-1]->d_name, key->d_name) > 0) {
                files[j] = files[j-1];
                j--;
            }
        }

        files[j] = key; //insert in right place
    }
    return files;
}