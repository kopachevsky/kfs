#ifndef KFS_KFS_H
#define KFS_KFS_H

#pragma once

#include <fuse.h>
#include <glusterfs/api/glfs.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>
#include <sysexits.h>


#include "kfs_fuse_functions.h"

static char* concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
char ABSOLUTE_PATH[PATH_MAX];


#endif //KFS_KFS_H
