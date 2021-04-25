#include <stdio.h>
#include <execinfo.h>

#define BUFSIZE 1024

struct STACK_INFO_DEF {
    int stacknum;
    void *stackbuffer[BUFSIZE];
    char **c_stack;
};
typedef struct STACK_INFO_DEF STACK_INFO;

STACK_INFO* get_stack_2_string();
int record_stack_2_file();
