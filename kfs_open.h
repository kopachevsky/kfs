#ifndef KFS_KFS_OPEN_H
#define KFS_KFS_OPEN_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs.h"

#pragma once

int kfs_open(const char* _pathname, struct fuse_file_info* _info);

#endif //KFS_KFS_OPEN_H
