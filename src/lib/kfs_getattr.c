#include "kfs_getattr.h"

int kfs_getattr(const char *path, struct stat *stbuf) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = lstat(fpath, stbuf);
    fprintf(stderr,"%s\n", "kfs getattr");
    fprintf(stderr, "%d\n", -errno);
    if (res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        res = xglfs_getattr(path, stbuf);
        fprintf(stderr,"%s\n", "xglfs getattr");
        fprintf(stderr, "%d\n", -errno);
        if (res == -1) {
            return -errno;
        }
    }
    return 0;
}
