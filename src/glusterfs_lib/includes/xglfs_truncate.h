#ifndef KFS_XGLFS_TRUNCATE_H
#define KFS_XGLFS_TRUNCATE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_truncate(const char *path, off_t size);

#endif //KFS_XGLFS_TRUNCATE_H
