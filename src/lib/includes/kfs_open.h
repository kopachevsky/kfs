#ifndef KFS_KFS_OPEN_H
#define KFS_KFS_OPEN_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"
#include "kfs_create.h"

#pragma once

int kfs_open(const char *path, struct fuse_file_info *fi);

#endif //KFS_KFS_OPEN_H
