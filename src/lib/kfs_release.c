#include <kfs_release.h>

int kfs_release(const char *path, struct fuse_file_info *fi) {
    (void) path;
    int fd = close(fi->fh);
    if (fd == -1) {
        return -errno;
    }
    return 0;
}