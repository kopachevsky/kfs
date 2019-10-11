#ifndef KFS_KFS_RMDIR_H
#define KFS_KFS_RMDIR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_rmdir(const char *path);

#endif //KFS_KFS_RMDIR_H
