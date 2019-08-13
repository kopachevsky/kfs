#ifndef KFS_KFS_RELEASEDIR_H
#define KFS_KFS_RELEASEDIR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_releasedir(const char* path, struct fuse_file_info* fi);

#endif //KFS_KFS_RELEASEDIR_H
