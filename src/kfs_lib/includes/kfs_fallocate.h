#ifndef KFS_KFS_FALLOCATE_H
#define KFS_KFS_FALLOCATE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_fallocate(const char *path, int mode, off_t offset, off_t length, struct fuse_file_info *fi);

#endif //KFS_KFS_FALLOCATE_H
