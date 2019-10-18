#ifndef KFS_KFS_STATFS_H
#define KFS_KFS_STATFS_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_statfs(const char *path, struct statvfs *stbuf);

#endif //KFS_KFS_STATFS_H
