#ifndef KFS_KFS_WRITE_H
#define KFS_KFS_WRITE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi);

#endif //KFS_KFS_WRITE_H
