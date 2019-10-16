#include "kfs_utimens.h"

int kfs_utimens(const char *path, const struct timespec tv[2], struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int res = utimensat(fi->fh, fpath, tv, AT_SYMLINK_NOFOLLOW);
    printf("kfs_utimens execute result : %d\n", res);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
