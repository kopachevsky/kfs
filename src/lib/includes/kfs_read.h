#ifndef KFS_KFS_READ_H
#define KFS_KFS_READ_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_read(const char* original_path, char* buf, size_t size, off_t offset, struct fuse_file_info* fi);

#endif //KFS_KFS_READ_H
