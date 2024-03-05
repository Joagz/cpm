#define PROJECT_NAME "PROJECT_NAME"
#define YEAR "YEAR"
#define COPYRIGHT_HOLDER "COPYRIGHT_HOLDER"

#define DEF_COPYRIGHT_HOLDER "[your name]"
#define DEF_PROJECT_NAME "my-project"

#define VAR_CHAR '?'

#define MAX_VAR 50

struct envar
{
    int pos;
    int end;
    char * value;
};

// returns the value of the env variable
char * var_value(char *envar);
// splits buffer in two parts by pos, appends replace_val into part1 
// and appends that result to part2
char * put_var(char * to_read, char * replace_val, int pos, int end);
// get variable position in buffer from start
struct envar * get_var(int start, char * buffer);

#define LICENSE_TXT "Copyright ?YEAR? ?COPYRIGHT_HOLDER? \n\
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the \"Software\"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:\n\n\
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software."

#define MAKEFILE_TXT "CC      = gcc\n\
CFLAGS  = -Wall -D_FORTIFY_SOURCE=2 -Werror=implicit-function-declaration\n\
BINS    = main.o\n\
MAIN    = ?PROJECT_NAME?\n\
ROOT    = ./\n\
# ============= GENERIC ACTIONS (BETTER KEEP) =============\n\
all: $(MAIN)\n\
$(MAIN): $(BINS)\n\
\t$(CC) $(CFLAGS) -o $(MAIN) $(BINS)\n\
%.o: $(ROOT)/%.c\n\
\t$(CC) $(CFLAGS) -c -o $@ $<\n\
clean: \n\
\trm -f $(BINS) $(MAIN)"

#define README_TXT "#?PROJECT_NAME?\nModify your readme file"

#define MAIN_TXT "// Created by cpm (C Project Manager) | Author: Joaquin Gomez\n\
\n\
#include <stdio.h>\n\
\n\
int main(int argc, char **argv) \n\
{\n\
    printf(\"Hello World from CPM!\");\n\
    return 0;\n\
}"

