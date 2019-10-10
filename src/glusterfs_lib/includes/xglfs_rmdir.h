#ifndef KFS_XGLFS_RMDIR_H
#define KFS_XGLFS_RMDIR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_rmdir(const char *path);

#endif //KFS_XGLFS_RMDIR_H
