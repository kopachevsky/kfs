#include "kfs_fsync.h"

int kfs_fsync(const char *path, int datasync, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    int res;
    if (datasync != 0) {
        res = fdatasync(fi->fh);
    } else {
        res = fsync(fi->fh);
        log_debugf("kfs_fsync execute result : %d\n", res);
    }
    if (res == -1) {
        log_errorf("Error kfs_fsync : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_fsync(path, datasync, fi);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}
