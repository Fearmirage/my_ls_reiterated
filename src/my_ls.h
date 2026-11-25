void simple_ls(char* dirname,int dot,int sort_by_modified);
int* get_options(int argc, char** argv);
int get_paths(int argc,char** argv,char* paths_arr[]);
int ls_on_all_paths(int* options,char** paths,int path_count);
int list(int argc,char** argv);