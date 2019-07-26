#ifndef KFS_KFS_LINK_H
#define KFS_KFS_LINK_H

#include <errno.h>
#include <glusterfs/api/glfs.h>

#include "kfs_common.h"

#pragma once

int kfs_link(const char* first_path, const char* second_path);

#endif //KFS_KFS_LINK_H
