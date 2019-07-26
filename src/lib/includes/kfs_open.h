#ifndef KFS_KFS_OPEN_H
#define KFS_KFS_OPEN_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_open(const char* path, mode_t mode);

#endif //KFS_KFS_OPEN_H
