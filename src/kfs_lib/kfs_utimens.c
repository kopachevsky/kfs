#include "kfs_utimens.h"

int kfs_utimens(const char *path, const struct timespec tv[2], struct fuse_file_info *fi) {
    char fpath[MAX];
    fullpath(fpath, path);
    int res = utimensat(fi->fh, fpath, tv, AT_SYMLINK_NOFOLLOW);
    printf("kfs_utimens execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        int ret = xglfs_utimens(path, tv);
        if (ret == -1) {
            return -errno;
        }
    }
    return 0;
}
