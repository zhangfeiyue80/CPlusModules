#include <stdio.h>
#include <vector>
#include <string>
#include <execinfo.h>
extern "C" {
//#include <dbsignal.h>
}

#define BUFSIZE 1024

using namespace std;

class SelfDebug {

public:
    SelfDebug();
    ~SelfDebug();
    int GetStack2File(char *path);
    vector<string> GetStack2String();
    int SetStack();

private:
    FILE *_dfile;
    void *_stackbuffer[BUFSIZE];
    int _stacknum;
};
