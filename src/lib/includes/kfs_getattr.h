#ifndef KFS_KFS_GETATTR_H
#define KFS_KFS_GETATTR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_getattr(const char* path, struct stat* _buffer);

#endif //KFS_KFS_GETATTR_H
