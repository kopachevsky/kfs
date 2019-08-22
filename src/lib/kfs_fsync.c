#include <kfs_fsync.h>

int kfs_fsync(const char* path, int datasync, struct fuse_file_info *fi) {
    (void) path;
    int res = datasync != 0 ? fdatasync(fi->fh) : fsync(fi->fh);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
