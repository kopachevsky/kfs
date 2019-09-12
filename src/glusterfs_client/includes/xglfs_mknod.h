#ifndef KFS_XGLFS_MKNOD_H
#define KFS_XGLFS_MKNOD_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_mknod(const char* _path, mode_t _mode, dev_t _dev);

#endif //KFS_XGLFS_MKNOD_H
