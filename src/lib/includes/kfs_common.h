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
#include "zlog.h"
#include "xglfs_fuse_operations.h"

#pragma once

char *MOUNT_PATH;
char *LOCAL_DISC_CACHE_PATH;
char *LOG_CONFIG_PATH;

char *str_concat(const char* s1, const char* s2);

void fullpath(char fpath[PATH_MAX], const char *path);

int logger(const char *msg);

#endif //KFS_COMMON
