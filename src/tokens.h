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



