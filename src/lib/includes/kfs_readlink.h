#ifndef KFS_KFS_READLINK_H
#define KFS_KFS_READLINK_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_readlink(const char* path, char* buf, size_t size);

#endif //KFS_KFS_READLINK_H
