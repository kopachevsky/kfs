#ifndef KFS_XGLFS_OPENDIR_H
#define KFS_XGLFS_OPENDIR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_opendir(const char *path, struct fuse_file_info *fi);

#endif //KFS_XGLFS_OPENDIR_H
