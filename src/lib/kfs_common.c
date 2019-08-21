#include <kfs_common.h>
#include "zlog.h"


char *str_concat(const char* s1, const char* s2) {
    assert(s1 && s2);
    size_t s1len = strlen(s1);
    size_t s2len = strlen(s2);
    assert(s1len && s2len);
    char *path = malloc(s1len + s2len + 2);
    if (!path) return NULL;
    strcpy(path, s1);
    if ((path[s1len - 1] != '/') && (s2[0] != '/')) {
        strcat(path, "/");
    } else if (path[s1len - 1] == '/') {
        while (s2[0] == '/') s2++;
    }
    strcat(path, s2);
    return path;
}

char *str_replace(char const *const original, char const *const pattern, char const *const replacement) {
    size_t const replen = strlen(replacement);
    size_t const patlen = strlen(pattern);
    size_t const orilen = strlen(original);

    size_t patcnt = 0;
    const char * oriptr;
    const char * patloc;

    // find how many times the pattern occurs in the original string
    for (oriptr = original; (patloc = (strstr(oriptr, pattern))); oriptr = patloc + patlen) {
        patcnt++;
    }

    // allocate memory for the new string
    size_t const retlen = orilen + patcnt * (replen - patlen);
    char * const returned = (char *) malloc( sizeof(char) * (retlen + 1) );

    if (returned != NULL) {
        // copy the original string,
        // replacing all the instances of the pattern
        char * retptr = returned;
        for (oriptr = original; (patloc = (strstr(oriptr, pattern))); oriptr = patloc + patlen) {
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

char *local_disk_cache_path(const char *path) {
    if (path[0] == '/') {
        return str_replace(path, MOUNT_PATH, LOCAL_DISC_CACHE_PATH);
    } else {
        char * res = str_concat(LOCAL_DISC_CACHE_PATH, path);
        return res;
    }
}

int log(const char *msg) {
    LOG_CONFIG_PATH = "/home/donelkostino/kfs/tests/assets/zlog.conf";
    static int rc;
    if (!rc) {
        rc = dzlog_init(LOG_CONFIG_PATH, "default");
    }
    if (rc) {
        printf("init failed\n");
        return -1;
    }
    dzlog_info(msg);
}
