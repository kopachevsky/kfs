#include "kfs_read.h"

int kfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    struct stat sbuf;
    int x = stat (fpath, &sbuf);
    if (x != 0 ) {
        fprintf(stderr, "Error reading file: %s\n", strerror( errno ));
        return -errno;
    }
    set_current_user();
    int res = pread(fi->fh, buf, size, offset);
    set_default_user();
    if (res == -1) {
        fprintf(stderr, "Error reading file: %s\n", strerror( errno ));
        return -errno;
    }
    return res;
}