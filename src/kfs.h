#ifndef KFS_KFS_H
#define KFS_KFS_H

#pragma once

#include <fuse.h>
#include <glusterfs/api/glfs.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <getopt.h>
#include <sysexits.h>

#include "lib/includes/kfs_getattr.h"
#include "lib/includes/kfs_access.h"
#include "lib/includes/kfs_open.h"
#include "lib/includes/kfs_read.h"
#include "lib/includes/kfs_write.h"
#include "lib/includes/kfs_truncate.h"
#include "lib/includes/kfs_release.h"
#include "lib/includes/kfs_readdir.h"
#include "lib/includes/kfs_unlink.h"
#include "lib/includes/kfs_rename.h"
#include "lib/includes/kfs_mkdir.h"
#include "lib/includes/kfs_rmdir.h"
#include "lib/includes/kfs_mknod.h"
#include "lib/includes/kfs_create.h"
#include "lib/includes/kfs_chmod.h"
#include "lib/includes/kfs_link.h"
#include "lib/includes/kfs_symlink.h"
#include "lib/includes/kfs_flush.h"
#include "lib/includes/kfs_ftruncate.h"
#include "lib/includes/kfs_readlink.h"
#include "lib/includes/kfs_fsync.h"

#endif //KFS_KFS_H
