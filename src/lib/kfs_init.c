#include "kfs_init.h"

void *kfs_init(struct fuse_conn_info *connection) {
    return xglfs_init(connection);
}

