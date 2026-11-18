#include "my_ls.h"

int main(int argc,char** argv){
    return list(argc,argv);
}

/* How to compare with ls:
$>./my_ls > my_ls.output
$>ls -1 > ls.output
$>diff my_ls.output ls.output
$>
*/