#include "xglfs_fsync.h"

int xglfs_fsync(const char *path, int datasync, struct fuse_file_info *fi) {
    (void)path;
    (void)fi;
    int res = 0;
    if (datasync) {
        res = glfs_fdatasync(FH_TO_FD(XGLFS_STATE->g_fh));
    } else {
        res = glfs_fsync(FH_TO_FD(XGLFS_STATE->g_fh));
    }
    if (res == -1) {
        return -errno;
    }
    return 0;
}
