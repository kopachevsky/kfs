#ifndef KFS_XGLFS_CREATE_H
#define KFS_XGLFS_CREATE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_create(const char* _path, mode_t _mode, struct fuse_file_info* _info);

#endif //KFS_XGLFS_CREATE_H
