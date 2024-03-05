#include "tokens.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SE struct envar

static char * get_var_value(char * varname)
{
    extern char * projname;
    if(strcmp(varname, PROJECT_NAME) == 0)
    {
        return projname;
    }

    if(strcmp(varname, YEAR) == 0)
    {
        time_t t = time(NULL);
        struct tm * time = localtime(&t);
        
        char * res = (char*) malloc(5);

        sprintf(res, "%d", 1900 + time->tm_year);
    
        return res;
    }

    if(strcmp(varname, COPYRIGHT_HOLDER) == 0)
    {  
        return DEF_COPYRIGHT_HOLDER;
    }

    return NULL;
}

struct envar * get_var(int start, char *buffer)
{
    struct envar    * res = (SE*) malloc(sizeof(SE));
    char            varname[50] = "";
    int i = start;
    for(; i < strlen(buffer); i++)
    {
        if(buffer[i] == VAR_CHAR)
        {

            i++;
            start=i;
            while(buffer[i] != VAR_CHAR) i++;

            memcpy(varname, buffer+start, i-start);
            
            break;
        }
        if( i == strlen(buffer)-1) return NULL;
    }

    res->pos    = start;
    res->value  = get_var_value(varname);
    res->end    = i;
    return res;

}

char * put_var(char *to_read, char *replace_val, int pos, int end)
{

    printf("Putting '%s'\n", replace_val);

    size_t size = strlen(to_read);

    char * part1 = (char*) malloc(pos + 1);
    char * part2 = (char*) malloc(size-end + 1);

    strncpy(part1, to_read, pos);

    part1[pos-1] = '\0';

    strncpy(part2, to_read + end + 1, size - end);
     
    char * result = malloc(strlen(part1) + strlen(part2) + strlen(replace_val));

    sprintf(result, "%s%s%s", part1, replace_val, part2);

    free(part1);
    free(part2);

    return result;
}

