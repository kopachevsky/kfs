#ifndef KFS_KFS_RELEASE_H
#define KFS_KFS_RELEASE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs.h"

#pragma once

int kfs_release(const char* path, struct fuse_file_info* info);

#endif //KFS_KFS_RELEASE_H
