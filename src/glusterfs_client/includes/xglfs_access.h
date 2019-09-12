#ifndef KFS_XGLFS_ACCESS_H
#define KFS_XGLFS_ACCESS_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_access(const char* _path, int _mask);

#endif //KFS_XGLFS_ACCESS_H
