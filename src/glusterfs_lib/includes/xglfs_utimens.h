#ifndef KFS_XGLFS_UTIMENS_H
#define KFS_XGLFS_UTIMENS_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_utimens(const char *path, const struct timespec tv[2]);

#endif //KFS_XGLFS_UTIMENS_H
