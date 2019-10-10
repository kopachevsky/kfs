#ifndef KFS_XGLFS_MKNOD_H
#define KFS_XGLFS_MKNOD_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_mknod(const char *path, mode_t mode, dev_t rdev);

#endif //KFS_XGLFS_MKNOD_H
