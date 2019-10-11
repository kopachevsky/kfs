#include "kfs_fsync.h"

int kfs_fsync(const char *path, int datasync, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    int res = datasync != 0 ? fdatasync(fi->fh) : fsync(fi->fh);
    if (res == -1) {
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
