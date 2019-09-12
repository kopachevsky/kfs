#ifndef KFS_XGLFS_CHOWN_H
#define KFS_XGLFS_CHOWN_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_chown(const char* _path, uid_t _owner, gid_t _group);

#endif //KFS_XGLFS_CHOWN_H
