#include <kfs_fsync.h>

int kfs_fsync(const char* original_path, int datasync, struct fuse_file_info *fi) {
    char *path = local_disk_cache_path(original_path);
    (void) path;
    int res = datasync != 0 ? fdatasync(fi->fh) : fsync(fi->fh);
    if (res == -1) {
        return -errno;
    }
    free(path);
    return 0;
}
