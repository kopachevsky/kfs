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
#include <pwd.h>

#include "zlog.h"
#include "xglfs_fuse_operations.h"

#pragma once

char *MOUNT_PATH;
char *LOCAL_DISC_CACHE_PATH;
char *LOG_CONFIG_PATH;

char *str_concat(const char *s1, const char *s2);

void fullpath(char fpath[PATH_MAX], const char *path);

void set_current_user();
void set_default_user();

int log_init();

void log_info(const char *msg);
void log_debug(const char *msg);
void log_error(const char *msg);

void log_infof(const char *msg, ...);
void log_debugf(const char *msg, ...);
void log_errorf(const char *msg, ...);


#endif //KFS_COMMON
