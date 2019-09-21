#ifndef KFS_XGLFS_GETATTR_H
#define KFS_XGLFS_GETATTR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_getattr(const char* _path, struct stat* _buffer);

#endif //KFS_XGLFS_GETATTR_H
