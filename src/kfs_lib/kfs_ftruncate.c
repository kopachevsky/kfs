#include "kfs_ftruncate.h"

int kfs_ftruncate(const char *path, off_t size, struct fuse_file_info *fi) {
    char fpath[MAX_PATH];
    fullpath(fpath, path);
    (void) fpath;
    printf("kfs_truncate fd : %lu\n", fi->fh);
    int res = ftruncate(fi->fh ,size);
    printf("kfs_ftruncate execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_ftruncate(path, size, fi);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;

}

