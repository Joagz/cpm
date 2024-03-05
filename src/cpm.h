#define MAX_READ 8192
#define MAX_VAR 50
#define MAX_LIBNAME 20
#define MAX_ARGC 7
#define DIR_PERMISSION 0777

#ifndef SOURCE_DIRECTORY
#define SOURCE_DIRECTORY ""
#endif

#define N_MAKEFILE "Makefile"
#define N_MAINC "main.c"
#define N_README "README.md"
#define N_LICENSE "LICENSE.txt"
#define N_LIBS_DIR "./libs"

#define SRC_MAKEFILE "/cpm-files/MakefileCOPY"
#define SRC_MAINC "/cpm-files/main"
#define SRC_README "/cpm-files/README.md"
#define SRC_LICENSE "/cpm-files/LICENSE.txt"

#define SE struct envar

void check_args(int argc);
void err_n_exit(void* ptr, char* msg);
int add_files(char * wdir, char *fdirloc, char *fincl);
int create_file(char * name, char * dir, char * read_from);
