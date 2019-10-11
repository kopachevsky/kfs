#ifndef KFS_KFS_MKNOD_H
#define KFS_KFS_MKNOD_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_mknod(const char *path, mode_t mode, dev_t rdev);

#endif //KFS_KFS_MKNOD_H
