#ifndef KFS_XGLFS_RELEASEDIR_H
#define KFS_XGLFS_RELEASEDIR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_releasedir(const char *path, struct fuse_file_info *fi);

#endif //KFS_XGLFS_RELEASEDIR_H
