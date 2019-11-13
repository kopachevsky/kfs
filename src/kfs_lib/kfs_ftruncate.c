#include "kfs_ftruncate.h"

int kfs_ftruncate(const char *path, off_t size, struct fuse_file_info *fi) {
    log_info("kfs_ftruncate start");
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_ftruncate path : %s\n", fpath);
    log_debugf("    kfs_ftruncate fd : %lu\n", fi->fh);
    (void) fpath;
    set_current_user();
    int res = ftruncate(fi->fh ,size);
    set_default_user();
    if (res == -1) {
        log_errorf("Error kfs_ftruncate : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_ftruncate(path, size, fi);
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_ftruncate exit result : %d\n", res);
    return 0;

}

