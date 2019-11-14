#ifndef KFS_KFS_UTIMENS_H
#define KFS_KFS_UTIMENS_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_utimens(const char *path, const struct timespec tv[2]);

#endif //KFS_KFS_UTIMENS_H
