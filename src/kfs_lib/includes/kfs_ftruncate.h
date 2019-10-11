#ifndef KFS_KFS_FTRUNCATE_H
#define KFS_KFS_FTRUNCATE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_ftruncate(const char *path, off_t size, struct fuse_file_info *fi);

#endif //KFS_KFS_FTRUNCATE_H
