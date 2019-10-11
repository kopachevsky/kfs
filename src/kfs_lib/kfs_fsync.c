#include "kfs_fsync.h"

int kfs_fsync(const char *path, int datasync, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    int res;
    if (datasync != 0) {
        printf("kfs_fsync datasync fd : %lu\n", fi->fh);
        res = fdatasync(fi->fh);
        printf("kfs_fsync datasync execute result : %d\n", res);
    } else {
        printf("kfs_fsync fd : %lu\n", fi->fh);
        res = fsync(fi->fh);
        printf("kfs_fsync execute result : %d\n", res);
    }
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
