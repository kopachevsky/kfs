#include "kfs_init.h"

void *kfs_init(struct fuse_conn_info *conn) {
    return xglfs_init(conn);
}

