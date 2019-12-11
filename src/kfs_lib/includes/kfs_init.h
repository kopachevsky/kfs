#ifndef KFS_KFS_INIT_H
#define KFS_KFS_INIT_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"
#include "copy_remote_storage_content.h"

#pragma once

void *kfs_init(struct fuse_conn_info *connection);

#endif //KFS_KFS_INIT_H
