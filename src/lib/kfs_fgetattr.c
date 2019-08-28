#include "kfs_fgetattr.h"

int kfs_fgetattr(const char *path, struct stat *stbuf,struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    int res = fstat(fi->fh, stbuf);
    if (res == -1) {
        return -errno;
    }
    return 0;
}
