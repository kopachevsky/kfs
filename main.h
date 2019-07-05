#include <map>
#include <string>
#include <iostream>
using namespace std;

extern "C" {

#define FUSE_USE_VERSION  26
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
