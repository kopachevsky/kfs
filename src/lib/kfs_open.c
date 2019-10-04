#include "kfs_open.h"

int kfs_open(const char* path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    if (fi->flags == O_CREAT) {
        int res = kfs_create(path, 0, fi);
        if (res == -1) {
            return -errno;
        }
    } else {
        int fd = open(fpath, fi->flags);
        fprintf(stderr, "%s\n", "kfs open");
        fprintf(stderr, "%d\n", -errno);
        if (fd == -1) {
            return -errno;
        }
        fi->fh = fd;
        if (XGLFS_STATE->gluster_api) {
            fd = xglfs_open(path, fi);
            fprintf(stderr, "%s\n", "xglfs open");
            fprintf(stderr, "%d\n", -errno);
            if (fd == -1) {
                return -errno;
            }
        }
    }
    return 0;
}
