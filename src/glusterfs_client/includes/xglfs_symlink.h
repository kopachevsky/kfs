#ifndef KFS_XGLFS_SYMLINK_H
#define KFS_XGLFS_SYMLINK_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_symlink(const char* _path1, const char* _path2);

#endif //KFS_XGLFS_SYMLINK_H
