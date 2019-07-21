#ifndef KFS_COMMON
#define KFS_COMMON

#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <fuse.h>

#pragma once
char ABSOLUTE_PATH[PATH_MAX];

static char* concat(const char *s1, const char *s2) {
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

#endif //KFS_COMMON
