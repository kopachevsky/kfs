#include <kfs_fsync.h>

int kfs_fsync(const char* original_path, int datasync, struct fuse_file_info *fi) {
    int res = datasync != 0 ? fdatasync(fi->fh) : fsync(fi->fh);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
