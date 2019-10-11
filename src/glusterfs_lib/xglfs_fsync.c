#include "xglfs_fsync.h"

int xglfs_fsync(const char *path, int datasync, struct fuse_file_info *fi) {
    (void)path;
    (void)fi;
    int res = 0;
    if (datasync) {
        printf("xglfs_fsync datasync fd : %lu\n", XGLFS_STATE->g_fh);
        res = glfs_fdatasync(FH_TO_FD(XGLFS_STATE->g_fh));
        printf("xglfs_fsync datasync execute result : %d\n", res);

    } else {
        printf("xglfs_fsync fd : %lu\n", XGLFS_STATE->g_fh);
        res = glfs_fsync(FH_TO_FD(XGLFS_STATE->g_fh));
        printf("xglfs_fsync execute result : %d\n", res);
    }
    if (res == -1) {
        return -errno;
    }
    return 0;
}
