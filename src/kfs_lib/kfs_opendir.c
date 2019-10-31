#include "kfs_opendir.h"

int kfs_opendir(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("kfs_opendir path : %s\n", fpath);
    DIR *dp = opendir(fpath);
    if (dp == NULL) {
        log_errorf("Error kfs_openDIR : %s\n", strerror( errno ));
        return -errno;
    }
    fi->fh = (intptr_t) dp;
    log_debugf("kfs_chown execute result : %lu\n", fi->fh);
    return 0;
}


