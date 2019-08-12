#ifndef KFS_COMMON
#define KFS_COMMON

#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <fuse.h>
#include <stdio.h>
#include <zconf.h>
#include <dirent.h>
#include <assert.h>

#pragma once

char *MOUNT_PATH;
char *LOCAL_DISC_CACHE_PATH;

char *str_concat(const char* s1, const char* s2);

char *str_replace(char const *original, char const *pattern, char const *replacement);

char *local_disk_cache_path(const char *path);

int remove_directory(const char *path);

struct kfs_dirp {
    DIR *dp;
    struct dirent *entry;
    off_t offset;
};

#endif //KFS_COMMON
