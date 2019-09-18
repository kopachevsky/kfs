#ifndef KFS_XGLFS_FSYNC_H
#define KFS_XGLFS_FSYNC_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_fsync(const char* _path, int _datasync, struct fuse_file_info* _info);

#endif //KFS_XGLFS_FSYNC_H
