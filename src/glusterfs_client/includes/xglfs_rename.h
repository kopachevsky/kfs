#ifndef KFS_XGLFS_RENAME_H
#define KFS_XGLFS_RENAME_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_rename(const char* _oldpath, const char* _newpath);

#endif //KFS_XGLFS_RENAME_H
