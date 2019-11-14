#include "kfs_fgetattr.h"

int kfs_fgetattr(const char *path, struct stat *stbuf,struct fuse_file_info *fi) {
    char fpath[PATH_MAX] = { 0 };
    log_debugf("  fpath : %s\n", fpath);
    fullpath(fpath, path);
    (void) fpath;
    int res = fstat(fi->fh, stbuf);
    log_debugf("kfs_fgetattr execute result : %d\n", res);
    if (res == -1) {
        log_errorf("Error kfs_fgetattr : %s\n", strerror( errno ));
        return -errno;
    }
    return 0;
}
