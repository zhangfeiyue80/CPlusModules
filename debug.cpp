/*
#ifndef _SELFDEBUG
    #define _SELFDEBUG
    #include "debug.hpp"
#endif
*/

#include "debug.hpp"

SelfDebug::SelfDebug() {
    _dfile=NULL;
}

SelfDebug::~SelfDebug() {
    if(_dfile!=NULL)
        fclose(_dfile);
}

// return value: -1 is failed, 0 is success.
int SelfDebug::GetStack2File(char *path) {
    _dfile = fopen(path, "a+");
    if (_dfile == NULL) return -1;
    backtrace_symbols_fd(_stackbuffer, _stacknum, fileno(_dfile));
    fprintf(_dfile, "\n");
    fflush(_dfile);
    return 0;
}

int SelfDebug::GetStack2String(vector<string> &vstr) {
    int i;
    char **cstr;
    string str;

    cstr = backtrace_symbols(_stackbuffer, _stacknum);
    for(i=0; i<_stacknum; i++) {
        str = cstr[i];
        vstr.push_back(str);
    }
    return 0;
}

int SelfDebug::SetStack() {
    _stacknum = backtrace(_stackbuffer, BUFSIZE);
    return 0;
}

// example
/* 
#include <DMMResource/debug.hpp>

Dbg dbg("Media::getNewRef ");
vector<string> vstr;
vector<string>::iterator i;
SelfDebug dmm_btdbg;
dmm_btdbg.SetStack();
dmm_btdbg.GetStack2File("/opt/DPX/logs/dmm_stack.txt");
dmm_btdbg.GetStack2String(vstr);
for (i=vstr.begin(); i != vstr.end(); ++i) {
    dbg(0) << *i << std::endl;
}
*/
