#ifndef KFS_KFS_READDIR_H
#define KFS_KFS_READDIR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);

#endif //KFS_KFS_READDIR_H
