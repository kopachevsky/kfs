#ifndef KFS_KFS_RENAME_H
#define KFS_KFS_RENAME_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_rename(const char* from, const char* to);

#endif //KFS_KFS_RENAME_H
