#ifndef KFS_XGLFS_OPENDIR_H
#define KFS_XGLFS_OPENDIR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_opendir(const char* _path, struct fuse_file_info* _info);

#endif //KFS_XGLFS_OPENDIR_H
