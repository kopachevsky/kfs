#include "xglfs_init.h"

void* xglfs_init(struct fuse_conn_info* _connection) {
    (void)_connection;
    XGLFS_STATE->fs = glfs_new(XGLFS_STATE->volume);
    if (unlikely(!XGLFS_STATE->fs)) {
        fprintf(stderr, "%s\n", "Unable to create GlusterFS instance");
        exit(EX_SOFTWARE);
    }
    if (unlikely(glfs_set_logging(XGLFS_STATE->fs, XGLFS_STATE->glfs_logfile, XGLFS_STATE->glfs_verbosity))) {
        fprintf(stderr, "%s\n", "Unable to set GlusterFS logging");
        exit(EX_SOFTWARE);
    }
    if (unlikely(glfs_set_volfile_server(XGLFS_STATE->fs, XGLFS_STATE->protocol, XGLFS_STATE->server, XGLFS_STATE->port))) {
        fprintf(stderr, "%s\n", "Unable to set GlusterFS volume file server");
        exit(EX_SOFTWARE);
    }
    if (unlikely(glfs_init(XGLFS_STATE->fs))) {
        fprintf(stderr, "%s\n", "Unable to initialize GlusterFS");
        exit(EX_SOFTWARE);
    }
    return XGLFS_STATE;
}
