#include "tokens.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SE struct envar

struct envar * get_var(int start, char *buffer)
{
    struct envar    * res = (SE*) malloc(sizeof(SE));
    char            * varname = (char*) malloc(MAX_VAR);

    int i = start;
    for(; i < strlen(buffer); i++)
    {
        if(buffer[i] == '%')
        {

            printf("Found at position %d\n",i);
            i++;
            start=i;
            while(buffer[i] != '%') i++;

            memcpy(varname, buffer+start, i-start);

            printf("%s\n", varname);
            
            break;
        }
        if( i == strlen(buffer)-1) return NULL;
    }

    res->pos    = start;
    res->value  = varname;
    res->end    = i+1;
    return res;

}

char * put_var(char *to_read, char *replace_val, int pos, int end)
{
    size_t size = strlen(to_read);

    char * part1 = (char*) malloc(pos + strlen(replace_val));
    char * part2 = (char*) malloc(size-pos);

    memcpy(part1, to_read, pos-1);
    part1[pos] = '\0';

    strcat(part1, replace_val);
    memcpy(part2, to_read + end, size + strlen(replace_val));
    
    char * result = malloc(size + strlen(replace_val));

    strcpy(result, part1);
    strcat(result, part2);

    return result;
}
int main(){
    char * str = "Hi %REPLACE%!";
    struct envar * var = get_var(0,str);

    char * new = put_var(str, "World", var->pos, var->end);

    printf("%s\n", new);

    return 0;
}
