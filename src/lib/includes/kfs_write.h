#ifndef KFS_KFS_WRITE_H
#define KFS_KFS_WRITE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_write(const char* path, const char* _buf, size_t _size, off_t _offset, struct fuse_file_info* _info);

#endif //KFS_KFS_WRITE_H
