#include "kfs_write.h"

int kfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    char fpath[PATH_MAX] = {0};
    fullpath(fpath, path);
    (void) fpath;
    set_current_user();
    int res = pwrite(fi->fh, buf, size, offset);
    set_default_user();
    log_debugf("kfs_write execute result : %d\n", res);
    if (res == -1) {
        log_errorf("Error kfs_write : %s\n", strerror( errno ));
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