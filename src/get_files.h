#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int get_num_of_files(char* filename,int dot);
struct dirent** get_all_files(char* filename, int len,int dot);
struct timespec get_when_last_modified(struct dirent* file1,char* parent_file);
void sort_paths(char** paths,size_t path_count);
int last_modif_compare(struct dirent* file1,struct dirent* file2,char* parent_file);
struct dirent** sort_files(struct dirent** files,int len,char* parent_file,int sort_by_modified);