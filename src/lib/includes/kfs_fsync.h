#ifndef KFS_KFS_FSYNC_H
#define KFS_KFS_FSYNC_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_fsync(const char* path, int datasync, struct fuse_file_info *fi);

#endif //KFS_KFS_FSYNC_H
