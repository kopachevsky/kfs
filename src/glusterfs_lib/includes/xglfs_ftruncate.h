#ifndef KFS_XGLFS_FTRUNCATE_H
#define KFS_XGLFS_FTRUNCATE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_ftruncate(const char *path, off_t size, struct fuse_file_info *fi);

#endif //KFS_XGLFS_FTRUNCATE_H
