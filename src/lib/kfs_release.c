#include <kfs_release.h>

int kfs_release(const char *path, struct fuse_file_info *fi) {
    return close(fi->fh);
}