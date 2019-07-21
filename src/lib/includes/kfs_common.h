#ifndef KFS_COMMON
#define KFS_COMMON

#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <fuse.h>
#include <stdio.h>

#pragma once

char *MOUNT_PATH;
char *LOCAL_DISC_CACHE_PATH;

static char * str_concat(char const *const str1, char const *const str2) {
    char s1[strlen(str1)], s2[strlen(str2)];
    strcpy(s1, str1);
    strcpy(s2, str2);
    char *res = strcat(s1, s2);
    return res;
}

static char *str_replace(char const *const original, char const *const pattern, char const *const replacement) {
    size_t const replen = strlen(replacement);
    size_t const patlen = strlen(pattern);
    size_t const orilen = strlen(original);

    size_t patcnt = 0;
    const char * oriptr;
    const char * patloc;

    // find how many times the pattern occurs in the original string
    for (oriptr = original; patloc = (strstr(oriptr, pattern)); oriptr = patloc + patlen) {
        patcnt++;
    }

    // allocate memory for the new string
    size_t const retlen = orilen + patcnt * (replen - patlen);
    char * const returned = (char *) malloc( sizeof(char) * (retlen + 1) );

    if (returned != NULL) {
        // copy the original string,
        // replacing all the instances of the pattern
        char * retptr = returned;
        for (oriptr = original; patloc = (strstr(oriptr, pattern)); oriptr = patloc + patlen) {
            size_t const skplen = patloc - oriptr;
            // copy the section until the occurence of the pattern
            strncpy(retptr, oriptr, skplen);
            retptr += skplen;
            // copy the replacement
            strncpy(retptr, replacement, replen);
            retptr += replen;
        }
        // copy the rest of the string.
        strcpy(retptr, oriptr);
    }
    return returned;
}

static char* local_disk_cache_path(const char *path) {
    if (path[0] == '/') {
        return str_replace(path, MOUNT_PATH, LOCAL_DISC_CACHE_PATH);
    } else {
        char * res = str_concat(LOCAL_DISC_CACHE_PATH, path);
        return res;
    }
}

#endif //KFS_COMMON
