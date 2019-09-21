#ifndef KFS_XGLFS_RELEASE_H
#define KFS_XGLFS_RELEASE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_release(const char* _path, struct fuse_file_info* _info);

#endif //KFS_XGLFS_RELEASE_H
