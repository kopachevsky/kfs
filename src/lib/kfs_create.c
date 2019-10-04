#include "kfs_create.h"

int kfs_create(const char* path, mode_t mode, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int fd = open(fpath, fi->flags, mode);
    fprintf(stderr, "%s\n", "kfs create");
    fprintf(stderr, "%d\n", -errno);
    if (fd == -1) {
        return -errno;
    }
    fi->fh = fd;
    if (XGLFS_STATE->gluster_api) {
        fd = xglfs_create(path, mode, fi);
        fprintf(stderr, "%s\n", "xglfs create");
        fprintf(stderr, "%d\n", -errno);
        if (fd == -1) {
            return -errno;
        }
    }
    return 0;
}
