#ifndef KFS_XGLFS_LINK_H
#define KFS_XGLFS_LINK_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "xglfs.h"

#pragma once

int xglfs_link(const char* _path1, const char* _path2);

#endif //KFS_XGLFS_LINK_H
