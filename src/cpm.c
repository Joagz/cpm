// * Author: Joaquin Gomez.
// * dateMDY: 03/01/2024
//
// C-Project-Manager is a tool that enables to create fast C project file structure
// with the basic utilities (Makefile, libs, and include libs)
//
// This project is made for my own sake, use it at your own risk.

#include <errno.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cpm.h"
#include "tokens.h"

const char* get_executable_directory() {
    char* path = malloc(1024);  // Adjust the size as needed
    if (path == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    // Use readlink to get the path of the executable
    ssize_t len = readlink("/proc/self/exe", path, 1024);
    if (len == -1) {
        perror("Error getting executable path");
        free(path);
        exit(EXIT_FAILURE);
    }

    // Null-terminate the string
    path[len] = '\0';

    // Find the last occurrence of '/' to get the directory
    char* last_slash = strrchr(path, '/');
    if (last_slash != NULL) {
        *last_slash = '\0';  // Null-terminate at the last slash
        return path;
    } else {
        free(path);
        return "";
    }
}

// global project name to use between functions
char * projname = "my-project";

// env vars on files
char *env_vars[] = {
    "PROJECT_NAME", "YEAR", "COPYRIGHT_HOLDER"
};

// define arguments for 'cpm' command
static struct option long_options[] =
{
    {"create", required_argument, NULL, 'c'},
    {"directory", required_argument, NULL, 'd'},
    {"include", required_argument, 0, 'i'},
};

int main(int argc, char ** argv)
{
    printf("Current source file directory: %s\n", get_executable_directory());

    check_args(argc);

    

    int RET_VALUE       = EXIT_SUCCESS;
    int c                  ;
    int incflag         = 0;    // include libs flag (-i "sqlite3, pthread, [...]")
    int cflag           = 0;    // create project flag (-c $(PROJECT_NAME))
    int dirflag         = 0;    // (optional) relative directory location (-d [DIR_LOCATION])
    char *cvalue        = NULL;
    char *dirvalue      = NULL;
    char *include       = NULL;
    int opterr          = 0;
    char *dir           = (char*) malloc(PATH_MAX); // alloc memory for working dir location

    // look for working directory and debug
    err_n_exit(getcwd(dir, PATH_MAX), "Couldn't get working directory");

    // parse args defined in 'long_options'
    while((c = getopt_long(argc, argv, "c:d:i", long_options, NULL)) != -1)
    {
        switch (c)
        {
            case 'c':
                cvalue      = optarg;
                cflag       = 1;
                break;
            case 'd':
                dirvalue    = optarg;
                dirflag     = 1;
                break;
            case 'i':
                include     = optarg;
                incflag     = 1;
                break;
        }
    }

    projname = cvalue;
    RET_VALUE = add_files(dir, dirvalue, include);

    free(dir);

    return RET_VALUE;
}

void check_args(int argc)
{
    if(argc <= 1 || argc > MAX_ARGC) {
        err_n_exit(NULL, "Invalid arg ammount, for help use -h");
    }

}

// debug & exit in case of a fatal error
void err_n_exit(void * ptr, char* msg)
{
   if(!ptr)
   {
        perror(msg);

        if(errno == 0)
        {
            printf("[INFO] (errno's value is 0, this error was thrown by the program)\n");
        }

        fflush(stdout);
        exit(errno);
   }
}

// write and add project files
//
//      ----------------------------------------------------------------
//      | PARAM  | DESCRIPTION                                         |
//      ----------------------------------------------------------------
//      |wdir    | working directory                                   |
//      |fdirloc | relative dir location (optional)                    |
//      |fproj   | project name (mandatory)                            |
//      |fincl   | list of libs to include (optional, comma-separated) |
//      ----------------------------------------------------------------
//
//      File structure after func. execution:
//          * Makefile
//          * /libs
//              * main.c
//              * /sqlite # if included
//          * [compiled output here]
//          * README.md
//          * LICENSE.md
//
int add_files(char * wdir, char *fdirloc, char *fincl)
{
    char *dir = NULL;

    if(fdirloc != NULL){
        char buf[PATH_MAX];
        dir = realpath(fdirloc, buf);

        // Create if directory doesn't exist
        if(dir == NULL) {
            dir = (char*) malloc(strlen(wdir) + strlen(fdirloc));
            strcpy(dir, wdir);
            if(fdirloc[0] != '\\' || fdirloc[0] != '/') strcat(dir, "/");
            strcat(dir, fdirloc);
            mkdir(dir, DIR_PERMISSION);
        }

    } else {
        dir = wdir;
    }

    printf("* Creating project inside '%s'\n", dir);

    create_file(N_MAKEFILE, dir, MAKEFILE_TXT);
    create_file(N_MAINC, dir, MAIN_TXT);
    create_file(N_README, dir, README_TXT);
    create_file(N_LICENSE, dir, LICENSE_TXT);

    char * buffer = (char*) malloc(PATH_MAX);
    strcpy(buffer, dir);
    strcat(buffer, "/libs");
    mkdir(buffer, DIR_PERMISSION);
    free(buffer);
    return EXIT_SUCCESS;
}

int create_file(char * name, char * dir, char * read_from)
{
    char * finalname = (char*) malloc(PATH_MAX); 
    strcpy(finalname, dir);
    strcat(finalname, "/");
    strcat(finalname, name);

    printf("Creating %s in %s\n", name, finalname);

    FILE * fptr;

    fptr = fopen(finalname, "w+");

    char * buffer = (char*) malloc(MAX_READ);

    strcpy(buffer, read_from);

    struct envar * var = (SE*) malloc(sizeof(SE));

    var->end=0;
    var->pos=0;
    var->value=NULL;

    while((var = get_var(var->end, buffer)) != NULL)
    {
        char * res = put_var(buffer, var->value, var->pos, var->end);

        printf("%s\n%d\n%d\n", var->value, var->pos, var->end);

        buffer = (char *) realloc(buffer, strlen(res));

        strcpy(buffer, res);
    }

    fwrite(buffer, 1, strlen(buffer), fptr);

    free(finalname);
    free(buffer);
    return EXIT_SUCCESS;
}
