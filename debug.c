#ifndef _SELFCDEBUG
    #define _SELFCDEBUG
    #include <debug.h>
#endif

STACK_INFO* get_stack_2_string() {
    static STACK_INFO stack_info;
    stack_info.stacknum = backtrace(stack_info.stackbuffer, BUFSIZE);
    stack_info.c_stack = backtrace_symbols(stack_info.stackbuffer, BUFSIZE);
    return &stack_info;
}

int record_stack_2_file() {
  FILE* fp;
  int i;
  STACK_INFO* pstack_info;
  pstack_info = get_stack_2_string();
  fp = fopen("/opt/DPX/logs/evthnd.stack", "a");
  if (fp == NULL) return -1;
  for(i=0; i < pstack_info->stacknum; i++) {
    fputs(pstack_info->c_stack[i], fp);
    fputs("\n", fp);
  }
  fclose(fp);
  return 0;
}

// example
/*
#include "debug.h"
record_stack_2_file();
*/

// example
/*
int i;
STACK_INFO* pstack_info;
pstack_info=get_stack_2_string();
for(i=0; i < pstack_info->stacknum; i++) {
  msg_print(0054, tm_str_id, 0L, pstack_info->c_stack[i]);
}
*/
