#include "kfs_opendir.h"

int kfs_opendir(const char *path, struct fuse_file_info *fi) {
    log_debugf("kfs_opendir start  %s\n", path);
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_opendir fullpath : %s\n", fpath);
    set_current_user();
    fuse_context_log();
    DIR *dp = opendir(fpath);
    set_default_user();
    if (dp == NULL) {
        log_errorf("Error kfs_openDIR : %s\n", strerror( errno ));
        return -errno;
    }
    fi->fh = (intptr_t) dp;
    log_debugf("kfs_opendir exit result : %lu\n", fi->fh);
    return 0;
}


