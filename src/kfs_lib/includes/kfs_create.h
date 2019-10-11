#ifndef KFS_KFS_CREATE_H
#define KFS_KFS_CREATE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_create(const char *path, mode_t mode, struct fuse_file_info *fi);

#endif //KFS_KFS_CREATE_H
