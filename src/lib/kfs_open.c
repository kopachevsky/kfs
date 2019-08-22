#include <kfs_open.h>

int kfs_open(const char* path, struct fuse_file_info *fi) {
    int fd = open(path, fi->flags);
    if (fd == -1) {
        return -errno;
    }
    fi ->fh = fd;
    return 0;
}
