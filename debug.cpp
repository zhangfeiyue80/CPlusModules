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
    return 0;
}

vector<string> SelfDebug::GetStack2String() {
    int i;
    char **cstr;
    vector<string> vstr;
    string str;

    cstr = backtrace_symbols(_stackbuffer, BUFSIZE);
    for(i=0; i<_stacknum; i++) {
        str = cstr[i];
        vstr.push_back(str);
    }
    return vstr;
}

int SelfDebug::SetStack() {
    _stacknum = backtrace(_stackbuffer, BUFSIZE);
    return 0;
}
