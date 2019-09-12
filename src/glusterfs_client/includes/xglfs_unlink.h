#ifndef KFS_XGLFS_UNLINK_H
#define KFS_XGLFS_UNLINK_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_unlink(const char* _path);

#endif //KFS_XGLFS_UNLINK_H
