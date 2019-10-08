#include "kfs_release.h"

int kfs_release(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    printf("kfs_release local fd : %lu\n", fi->fh);
    int fd = close(fi->fh);
    if (fd == -1) {
        return -errno;
    }
//    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_release(path, fi);
        if (ret == -1) {
            return -errno;
        }
//    }
    return 0;
}