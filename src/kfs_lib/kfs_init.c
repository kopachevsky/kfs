#include "kfs_init.h"

void *kfs_init(struct fuse_conn_info *connection) {
    log_init();
    log_info("kfs_init start");
    void* res =  XGLFS_STATE;
    if (XGLFS_STATE->gluster_sync) {
        log_info("   gluster sync enabled");
        res = xglfs_init(connection);
//        if (read_cluster() != 0) {
//            exit(EX_NOINPUT);
//        }
    } else {
        log_info("   gluster sync disabled");
    }
    log_info("kfs_init end");
    return res;
}
