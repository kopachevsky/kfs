#ifndef KFS_XGLFS_FGETATTR_H
#define KFS_XGLFS_FGETATTR_H

#include <errno.h>
#include <glusterfs/api/glfs.h>
#include <string.h>

#include "xglfs.h"
#include "xglfs_getattr.h"

#pragma once

int xglfs_fgetattr(const char* _path, struct stat* _statbuf, struct fuse_file_info* _info);

#endif //KFS_XGLFS_FGETATTR_H
