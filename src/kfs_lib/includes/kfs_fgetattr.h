#ifndef KFS_KFS_FGETATTR_H
#define KFS_KFS_FGETATTR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_fgetattr(const char *path, struct stat *stbuf,struct fuse_file_info *fi);

#endif //KFS_KFS_FGETATTR_H
