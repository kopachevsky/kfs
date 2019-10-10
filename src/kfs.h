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

#include "lib/includes/kfs_fuse_operations.h"
#include "glusterfs_lib/includes/xglfs_fuse_operations.h"

#endif //KFS_KFS_H
