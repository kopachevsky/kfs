#include <kfs_ftruncate.h>

int kfs_ftruncate(const char* original_path, off_t size, struct fuse_file_info *fi) {
    int res = ftruncate(fi->fh ,size);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
