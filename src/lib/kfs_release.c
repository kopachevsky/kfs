#include <kfs_release.h>

int kfs_release(const char *original_path, struct fuse_file_info *fi) {
    int fd = close(fi->fh);
    if (fd == -1) {
        return -errno;
    }
    return 0;
}