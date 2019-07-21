#ifndef KFS_KFS_UNLINK_H
#define KFS_KFS_UNLINK_H

#include <errno.h>
#include <glusterfs/api/glfs.h>
#include <zconf.h>

#include "kfs_common.h"

#pragma once

int kfs_unlink(const char* path);

#endif //KFS_KFS_UNLINK_H
