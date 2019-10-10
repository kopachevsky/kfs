#ifndef KFS_XGLFS_OPEN_H
#define KFS_XGLFS_OPEN_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_open(const char *path, struct fuse_file_info *fi);

#endif //KFS_XGLFS_OPEN_H
