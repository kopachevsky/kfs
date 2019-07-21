#ifndef KFS_KFS_ACCESS_H
#define KFS_KFS_ACCESS_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once
char ABSOLUTE_PATH[PATH_MAX];
int kfs_access(const char* path, int mask);


#endif //KFS_KFS_ACCESS_H
