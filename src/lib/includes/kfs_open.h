#ifndef KFS_KFS_OPEN_H
#define KFS_KFS_OPEN_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_open(const char* original_path, struct fuse_file_info *fi);

#endif //KFS_KFS_OPEN_H
