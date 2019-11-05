#ifndef KFS_XGLFS_READDIR_H
#define KFS_XGLFS_READDIR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi);

#endif //KFS_XGLFS_READDIR_H
