#include "kfs_fgetattr.h"

int kfs_fgetattr(const char *path, struct stat *stbuf,struct fuse_file_info *fi) {
    log_debugf("kfs_fgetattr start %s\n", path);
    fuse_context_log();
    char fpath[PATH_MAX] = {0};;
    fullpath(fpath, path);
    log_debugf("    kfs_fgetattr fullpath : %s\n", fpath);
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
