#ifndef KFS_XGLFS_STATFS_H
#define KFS_XGLFS_STATFS_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_statfs(const char *path, struct statvfs *buf);

#endif //KFS_XGLFS_STATFS_H
