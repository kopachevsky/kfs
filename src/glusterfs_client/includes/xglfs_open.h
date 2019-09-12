#ifndef KFS_XGLFS_OPEN_H
#define KFS_XGLFS_OPEN_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_open(const char* _pathname, struct fuse_file_info* _info);

#endif //KFS_XGLFS_OPEN_H
