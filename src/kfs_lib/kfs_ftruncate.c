#include "kfs_ftruncate.h"

int kfs_ftruncate(const char *path, off_t size, struct fuse_file_info *fi) {
    log_debugf("kfs_ftruncate start  %s\n", path);
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_ftruncate fullpath : %s\n", fpath);
    log_debugf("    kfs_ftruncate fd : %lu\n", fi->fh);
    (void) fpath;
    set_current_user();
    fuse_context_log();
    int res = ftruncate(fi->fh ,size);
    set_default_user();
    if (res == -1) {
        log_errorf("Error kfs_ftruncate : %s\n", strerror( errno ));
        return -errno;
    }
    if (XGLFS_STATE->gluster_sync) {
        xglfs_set_current_user();
        int ret = xglfs_ftruncate(path, size, fi);
        set_default_user();
        if (ret == -1) {
            return -errno;
        }
    }
    log_debugf("kfs_ftruncate exit result : %d\n", res);
    return 0;

}

