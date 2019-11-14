#include "kfs_read.h"

int kfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    log_debugf("kfs_read start  %s\n", path);
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    log_debugf("    kfs_read fullpath : %s\n", fpath);
    log_debugf("    kfs_read fd : %lu\n", fi->fh);
    (void) fpath;
    struct stat sbuf;
    int x = stat (fpath, &sbuf);
    if (x != 0 ) {
        fprintf(stderr, "Error reading file: %s\n", strerror( errno ));
        return -errno;
    }
    set_current_user();
    fuse_context_log();
    int res = pread(fi->fh, buf, size, offset);
    set_default_user();
    if (res == -1) {
        fprintf(stderr, "Error reading file: %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("kfs_read exit result : %d\n", res);
    return res;
}