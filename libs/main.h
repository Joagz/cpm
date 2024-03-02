
#define MAX_INCLUDE_ARGS 50
#define MAX_LIBNAME 20
#define MAX_ARGC 7
#define DIR_PERMISSION 0777

void check_args(int argc);
void err_n_exit(void* ptr, char* msg);
int add_files(char * wdir, char *fdirloc, char *fproj, char *fincl); 
