#ifndef KFS_XGLFS_CREATE_H
#define KFS_XGLFS_CREATE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_create(const char *path, mode_t mode, struct fuse_file_info *fi);

#endif //KFS_XGLFS_CREATE_H
