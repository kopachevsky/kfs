#ifndef KFS_KFS_CHMOD_H
#define KFS_KFS_CHMOD_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_chmod(const char *path, mode_t mode);

#endif //KFS_KFS_CHMOD_H
