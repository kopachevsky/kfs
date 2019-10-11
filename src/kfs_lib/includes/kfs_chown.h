#ifndef KFS_KFS_CHOWN_H
#define KFS_KFS_CHOWN_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_chown(const char *path, uid_t uid, gid_t gid);

#endif //KFS_KFS_CHOWN_H
