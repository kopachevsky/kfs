#ifndef KFS_KFS_READ_H
#define KFS_KFS_READ_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs.h"

#pragma once

int kfs_read(const char* path, char* _buf, size_t _size, off_t _offset, struct fuse_file_info* _info);

#endif //KFS_KFS_READ_H
