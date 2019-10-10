#ifndef KFS_XGLFS_CHOWN_H
#define KFS_XGLFS_CHOWN_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_chown(const char *path, uid_t uid, gid_t gid);

#endif //KFS_XGLFS_CHOWN_H
