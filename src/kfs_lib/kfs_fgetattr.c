#include "kfs_fgetattr.h"

int kfs_fgetattr(const char *path, struct stat *stbuf,struct fuse_file_info *fi) {
    log_info("kfs_fgetattr start");
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_fgetattr path : %s\n", fpath);
    log_debugf("    kfs_fgetattr fd : %lu\n", fi->fh);
    (void) fpath;
    int res = fstat(fi->fh, stbuf);
    if (res == -1) {
        log_errorf("Error kfs_fgetattr : %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("kfs_fgetattr exit result : %d\n", res);
    return 0;
}
