#ifndef KFS_XGLFS_FSYNC_H
#define KFS_XGLFS_FSYNC_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_fsync(const char *path, int datasync, struct fuse_file_info *fi);

#endif //KFS_XGLFS_FSYNC_H
