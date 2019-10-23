#include "kfs_flush.h"

int kfs_flush(const char *path, struct fuse_file_info *fi) {
    char fpath[MAX_PATH];
    fullpath(fpath, path);
    (void) fpath;
    int res = close(fi->fh);
    printf("kfs_flush execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return 0;
}