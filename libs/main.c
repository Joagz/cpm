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
#include "main.h"

// global project name to use between functions
static char * projname = "my-project";

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
      
        printf("dir %s\n", dir);

        // Create if directory doesn't exist
        if(dir == NULL) {
            printf("dir is null, let's change it\n");
            dir = (char*) malloc(strlen(wdir) + strlen(fdirloc));
            strcpy(dir, wdir);
            strcat(dir, fdirloc);
            printf("dir %s\n", dir);
            mkdir(dir, DIR_PERMISSION);
        }

    } else {
        dir = wdir;
    }

    printf("* Creating project inside '%s'\n", dir);

    char buf[PATH_MAX]; 
    create_file(N_MAKEFILE, dir, SRC_MAKEFILE);
    create_file(N_MAINC, dir, SRC_MAINC);
    create_file(N_README, dir, SRC_README);
    create_file(N_LICENSE, dir, SRC_LICENSE);

    char * buffer = malloc(PATH_MAX);
    strcpy(buffer, dir);
    strcat(buffer, "/libs");
    mkdir(buffer, DIR_PERMISSION);
    free(buffer);
    printf("DEBUG:\n\t%s\n\t%s\n\t%s", wdir, fdirloc, fincl);

    return EXIT_SUCCESS;
}

int create_file(char * name, char * dir, char * read_from)
{
    printf("Creating files... \n");
    printf("DEBUG\n\t%s\n\t%s\n\t%s\n",name, dir, read_from);

    char * finalname = (char*) malloc(PATH_MAX);
    strcpy(finalname, dir);
    strcat(finalname, "/");
    strcat(finalname, name);

    FILE * fptr;
    FILE * srcptr;

    srcptr = fopen(read_from, "r+");
    fptr = fopen(finalname, "w+");

    size_t bytes_read = 0;
    char * buffer = (char*) malloc(MAX_READ);

    int numread = fread(buffer, 1, MAX_READ, srcptr);
    printf("READ %d BYTES FROM %s\n", numread, read_from);
    fwrite(buffer, 1, numread, fptr);

    free(finalname);
    free(buffer);
    return EXIT_SUCCESS;
}
