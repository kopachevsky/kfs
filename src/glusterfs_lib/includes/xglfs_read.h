#ifndef KFS_XGLFS_READ_H
#define KFS_XGLFS_READ_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);

#endif //KFS_XGLFS_READ_H
