#ifndef KFS_XGLFS_WRITE_H
#define KFS_XGLFS_WRITE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_write(const char *path, const char *buf, size_t _size, off_t offset, struct fuse_file_info *fi);

#endif //KFS_XGLFS_WRITE_H
