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
#include <unistd.h>
#include <getopt.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "main.h"

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
  
    RET_VALUE = add_files(dir, dirvalue, cvalue, include);

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
   if((ptr) == NULL)
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
int add_files(char * wdir, char *fdirloc, char *fproj, char *fincl) 
{
    char *dir = NULL;

    if(fdirloc != NULL){
        char buf[PATH_MAX]; 
        dir = realpath(fdirloc, buf);
       
        // Create if directory doesn't exist
        if(!dir){
            dir = (char*) malloc(strlen(wdir) + strlen(fdirloc));
            strcpy(wdir, dir);
            strcat(fdirloc, dir);
            mkdir(dir, DIR_PERMISSION);
        }

    } else {
        dir = wdir;
    }

    printf("* Creating project inside '%s'\n", dir);

    // create files


    FILE * makefile_ptr;
    FILE * mainc_ptr;
    FILE * readme_ptr;
    FILE * license_ptr;
    
         



    printf("DEBUG:\n\t%s\n\t%s\n\t%s\n\t%s", wdir, fdirloc, fproj, fincl);

    return EXIT_SUCCESS;
}


