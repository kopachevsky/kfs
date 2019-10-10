#ifndef KFS_XGLFS_SYMLINK_H
#define KFS_XGLFS_SYMLINK_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_symlink(const char *source_path, const char *target_path);

#endif //KFS_XGLFS_SYMLINK_H
