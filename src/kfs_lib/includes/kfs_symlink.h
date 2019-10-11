#ifndef KFS_KFS_SYMLINK_H
#define KFS_KFS_SYMLINK_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_symlink(const char *source_path, const char *target_path);

#endif //KFS_KFS_SYMLINK_H
