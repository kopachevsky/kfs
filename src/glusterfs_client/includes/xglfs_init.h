#ifndef KFS_XGLFS_INIT_H
#define KFS_XGLFS_INIT_H

#include <glusterfs/api/glfs.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "xglfs.h"

#pragma once

void *xglfs_init(struct fuse_conn_info *connection);

#endif //KFS_XGLFS_INIT_H
