#include "kfs_write.h"

int kfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    printf("kfs_write fd : %lu\n", fi->fh);
    int res = pwrite(fi->fh, buf, size, offset);
    printf("kfs_write execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_write(path, buf, size, offset, fi);
        if (ret == -1) {
            return -errno;
        }
    }
    return res;
}