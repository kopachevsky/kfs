#include <map>
#include <string>
#include <iostream>
using namespace std;

extern "C" {}

#define FUSE_USE_VERSION  26
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

typedef map<int, unsigned char> FileContents;
typedef map<string, FileContents> FileMap;
static FileMap files;

static bool file_exists(string filename) {
    bool b = files.find(filename) != files.end();
    cout << "file_exists: " << filename << ": " << b << endl;
    return b;
}


FileContents to_map(string data) {
    FileContents data_map;
    int i = 0;

    for (string::iterator it = data.begin(); it < data.end(); ++it)
        data_map[i++] = *it;

    return data_map;
}

static string strip_leading_slash(string filename) {
    bool starts_with_slash = false;

    if( filename.size() > 0 )
        if( filename[0] == '/' )
            starts_with_slash = true;

    return starts_with_slash ? filename.substr(1, string::npos) : filename;
}
