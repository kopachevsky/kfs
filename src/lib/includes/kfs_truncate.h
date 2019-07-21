#ifndef KFS_KFS_TRUNCATE_H
#define KFS_KFS_TRUNCATE_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_truncate(const char* path, off_t length);

#endif //KFS_KFS_TRUNCATE_H
