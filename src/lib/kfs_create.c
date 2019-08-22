#include "kfs_create.h"

int kfs_create(const char* path, mode_t mode, struct fuse_file_info *fi) {
    int fd = open(path, fi->flags, mode);
    if (fd == -1) {
        return -errno;
    }
    fi->fh = fd;
    return 0;
}
